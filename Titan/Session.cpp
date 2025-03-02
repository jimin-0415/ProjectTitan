/**********************************************************************************************************************
* @file  Session.cpp
*
* @brief Session 클래스 cpp 파일
*
* @date  2025.02.24
**********************************************************************************************************************/


#include "pch.h"
#include "Session.h"
#include "Service.h"
#include "SocketUtil.h"
#include "NetAddress.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
Session::Session()
{
    _socket = SocketUtil::CreateSocket();
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
Session::~Session()
{
    SocketUtil::Close( _socket );
}

/**********************************************************************************************************************
* @brief 송신 한다
**********************************************************************************************************************/
ExVoid Session::Send( BYTE* buffer, ExInt32 len )
{
    // 생각할 문제.
    // 1. 버퍼를 어떻게 할지.
    // 2. SendEvent 관리? 단일 or 여러개? WSASend 중첩??

    // Temp
    IocpSendEvent* sendEvent = new IocpSendEvent();
    sendEvent->SetOwner( shared_from_this() );
    sendEvent->Buffer.resize( len );
    ::memcpy( sendEvent->Buffer.data(), buffer, len );

    WRITE_LOCK;
    _RegisterSend( sendEvent );
}

/**********************************************************************************************************************
* @brief 연결 한다
**********************************************************************************************************************/
ExBool Session::Connect()
{
    if ( false == _RegisterConnect() )
        return false;

    return true;
}

/**********************************************************************************************************************
* @brief 연결을 끊는다
**********************************************************************************************************************/
ExVoid Session::Disconnect( const WCHAR* cause )
{
    if ( false == _connected.exchange( false ) )
        return;

    wcout << "Disconnect:" << cause << endl;

    OnDisconnected();
    if ( auto service = GetService() )
        service->ReleaseSession( GetSessionPtr() );

    _RegisterDisconnect();
}

/**********************************************************************************************************************
* @brief 네트워크 주소를 설정한다
**********************************************************************************************************************/
ExVoid Session::SetNetAddress( NetAddress netAddress )
{
    return ExVoid();
}

/**********************************************************************************************************************
* @brief 핸들러를 반환한다
**********************************************************************************************************************/
HANDLE Session::GetHandle()
{
    return reinterpret_cast<HANDLE>( _socket );
}

/**********************************************************************************************************************
* @brief 처리한다
**********************************************************************************************************************/
void Session::Dispatch( IocpEvent* iocpEvent, ExInt32 numOfBytes )
{
    switch ( iocpEvent->GetType() )
    {
    case EIocpEventType::Connect: _ProcessConnect(); break;
    case EIocpEventType::Disconnect:
        _ProcessDisconnect();
        break;
    case EIocpEventType::Recv:
        _ProcessRecv( numOfBytes );
        break;
    case EIocpEventType::Send:
        _ProcessSend( static_cast<IocpSendEvent*>( iocpEvent ), numOfBytes );
        break;
    }
}

/**********************************************************************************************************************
* @brief 연결 되었을 때 처리한다
**********************************************************************************************************************/
ExVoid Session::OnConnected()
{
    return ExVoid();
}

/**********************************************************************************************************************
* @brief 연결이 끊어졌을 때 처리한다
**********************************************************************************************************************/
ExVoid Session::OnDisconnected()
{
    return ExVoid();
}

/**********************************************************************************************************************
* @brief 데이터가 송신되었을 때 처리한다
**********************************************************************************************************************/
ExVoid Session::OnSent( ExInt32 len )
{
    return ExVoid();
}

/**********************************************************************************************************************
* @brief 데이터가 수신되었을 때 처리한다
**********************************************************************************************************************/
ExInt32 Session::OnReceived( BYTE* buffer, ExInt32 len )
{
    return ExInt32();
}

/**********************************************************************************************************************
* @brief 연결을 등록한다
**********************************************************************************************************************/
ExBool Session::_RegisterConnect()
{
    if ( _connected )
        return false;

    if ( GetService()->GetServiceType() != EServiceType::Client )
        return false;

    if ( false == SocketUtil::SetReuseAddress( _socket, true ) )
        return false;

    // port는 남는것 중 하나
    if ( false == SocketUtil::BindAnyAdress( _socket, 0 ) )
        return false;

    _connectEvent.Clear();
    _connectEvent.SetOwner( shared_from_this() );
    
    DWORD numofBytes = 0;
    const SOCKADDR_IN& sockAddr = GetService()->GetNetAddress().GetSockAddr();
    if ( false == SocketUtil::ConnectEx(
        _socket,
        reinterpret_cast<const SOCKADDR*>( &sockAddr ),
        sizeof( sockAddr ),
        nullptr,
        0,
        &numofBytes,
        &_connectEvent ) )
    {
        ExInt32 errorCode = ::WSAGetLastError();
        if ( errorCode != WSA_IO_PENDING )
        {
            _HandleError( errorCode );
            _recvEvent.SetOwner( nullptr );
            return false;
        }
    }

    return true;
}

/**********************************************************************************************************************
* @brief 연결 종료를 등록한다
**********************************************************************************************************************/
ExBool Session::_RegisterDisconnect()
{
    _disconnectEvent.Clear();
    _disconnectEvent.SetOwner( shared_from_this() );

    // Disconnect 시 소켓 재사용
    if ( false == SocketUtil::DisconnectEx( _socket, &_disconnectEvent, TF_REUSE_SOCKET, 0 ) )
    {
        ExInt32 errorCode = ::WSAGetLastError();
        if ( errorCode == WSA_IO_PENDING )
        {
            _disconnectEvent.SetOwner( nullptr );
            return false;
        }
    }

    return true;
}

/**********************************************************************************************************************
* @brief 수신을 등록한다
**********************************************************************************************************************/
ExVoid Session::_RegisterRecv()
{
    if ( false == _connected )
        return;

    _recvEvent.Clear();
    _recvEvent.SetOwner( shared_from_this() );

    WSABUF wsaBuf;
    wsaBuf.buf = reinterpret_cast<char*>( _recvBuffer );
    wsaBuf.len = len32( _recvBuffer );

    DWORD numOfBytes = 0;
    DWORD flags = 0;

    if ( SOCKET_ERROR == ::WSARecv( _socket, &wsaBuf, 1, OUT &numOfBytes, OUT &flags, &_recvEvent, nullptr ) )
    {
        ExInt32 errorCode = ::WSAGetLastError();
        if ( errorCode != WSA_IO_PENDING )
        {
            _HandleError( errorCode );
            _recvEvent.SetOwner( nullptr );
        }
    }
}

/**********************************************************************************************************************
* @brief 송신을 등록한다
**********************************************************************************************************************/
ExVoid Session::_RegisterSend( IocpSendEvent* sendEvent )
{
    if ( false == _connected )
        return;

    WSABUF wsaBuf;
    wsaBuf.buf = (char*) sendEvent->Buffer.data();
    wsaBuf.len = (ULONG) sendEvent->Buffer.size();

    DWORD numOfBytes = 0;
    if ( SOCKET_ERROR == ::WSASend( _socket, &wsaBuf, 1, OUT & numOfBytes, 0, sendEvent, nullptr ) )
    {
        ExInt32 errorCode = ::WSAGetLastError();
        if ( errorCode != WSA_IO_PENDING )
        {
            _HandleError( errorCode );
            _recvEvent.SetOwner( nullptr );
            delete sendEvent;
        }
    }

    return ExVoid();
}

/**********************************************************************************************************************
* @brief 연결을 수행한다
**********************************************************************************************************************/
ExVoid Session::_ProcessConnect()
{
    _connectEvent.SetOwner( nullptr );
    _connected.store( true );

    // 세션 등록
    GetService()->AddSession( GetSessionPtr() );

    // 컨텐츠 로직 실행
    OnConnected();

    // 수신 등록
    _RegisterRecv();
}

/**********************************************************************************************************************
* @brief 연결 종료를 수행한다
**********************************************************************************************************************/
ExVoid Session::_ProcessDisconnect()
{
    _disconnectEvent.SetOwner( nullptr );
}

/**********************************************************************************************************************
* @brief 수신을 수행한다
**********************************************************************************************************************/
ExVoid Session::_ProcessRecv( ExInt32 numOfBytes )
{
    _recvEvent.SetOwner( nullptr );

    if ( 0 == numOfBytes )
    {
        Disconnect( L"Recv byte is zero!!!" );
        return;
    }

    OnReceived( _recvBuffer, numOfBytes );
    
    // 수신 등록
    _RegisterRecv();
}

/**********************************************************************************************************************
* @brief 송신을 수행한다
**********************************************************************************************************************/
ExVoid Session::_ProcessSend( IocpSendEvent* sendEvent, ExInt32 numOfBytes )
{
    sendEvent->SetOwner( nullptr );
    delete sendEvent;

    if ( 0 == numOfBytes )
    {
        Disconnect( L"Send is zero!!" );
        return;
    }

    OnSent( numOfBytes );
}

/**********************************************************************************************************************
* @brief 핸들 에러를 처리한다
**********************************************************************************************************************/
ExVoid Session::_HandleError( ExInt32 errorCode )
{
    switch ( errorCode )
    {
    case WSAECONNRESET:
    case WSAECONNABORTED:
        Disconnect( L"Handle Error!!" );
        break;
    default:
        // TODO : LOG
        cout << "Handle Erro :" << errorCode << endl;
        break;
    }
}

/**********************************************************************************************************************
* @file  Listener.cpp
*
* @brief Listener 클래스 cpp 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#include "pch.h"
#include "Listener.h"
#include "Session.h"
#include "SocketUtil.h"
#include "ServerService.h"
#include "IocpEvent.h"
#include "IocpCore.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
Listener::~Listener()
{
    SocketUtil::Close( _listener );

    for ( auto acceptEvent : _iocpAcceptEventList )
        delete acceptEvent;
}

/**********************************************************************************************************************
* @brief 연결 수락을 시작한다
**********************************************************************************************************************/
ExBool Listener::StartAccept( ServerServicePtr service )
{
    _service = service;
    if ( nullptr == _service )
        return false;
    
    _listener = SocketUtil::CreateSocket();
    if ( INVALID_SOCKET == _listener )
        return false;

    if ( service->GetIocpCore()->Register( shared_from_this() ) == false )
        return false;

    if ( SocketUtil::SetReuseAddress( _listener, true ) == false )
        return false;

    if ( SocketUtil::SetLinger( _listener, 0, 0 ) == false )
        return false;

    // net Address binding 
    if ( SocketUtil::Bind( _listener, service->GetNetAddress() ) == false )
        return false;

    if ( SocketUtil::Listen( _listener ) == false )
        return false;

    const ExInt32 acceptCount = 1;
    for ( ExInt32 i = 0; i < acceptCount; i++ )
    {
        IocpAcceptEvent* acceptEvent = new IocpAcceptEvent();
        acceptEvent->SetOwner( this->shared_from_this() );

        _iocpAcceptEventList.push_back( acceptEvent );
        _RegisterAccept( acceptEvent );
    }

    return true;
}

/**********************************************************************************************************************
 * @brief 소켓을 종료한다.
**********************************************************************************************************************/
ExVoid Listener::CloseSocket()
{
    SocketUtil::Close( _listener );
}

/**********************************************************************************************************************
 * @brief 핸들러를 반환한다.
**********************************************************************************************************************/
HANDLE Listener::GetHandle()
{
    return reinterpret_cast<HANDLE>( _listener );
}

/**********************************************************************************************************************
 * @brief 처리한다.
**********************************************************************************************************************/
void Listener::Dispatch( IocpEvent* iocpEvent, ExInt32 numOfBytes )
{
    switch ( iocpEvent->GetType() )
    {
        case EIocpEventType::Accept:
        {
            IocpAcceptEvent* acceptEvent = static_cast<IocpAcceptEvent*>( iocpEvent );
            _ProcessAccept( acceptEvent );
        } break;
    }
}

/**********************************************************************************************************************
 * @brief 연결 수락 이벤트를 등록한다.
**********************************************************************************************************************/
ExVoid Listener::_RegisterAccept( IocpAcceptEvent* acceptEvent )
{
    // Accept 예약한다.
    // Register IOCP
    SessionPtr session = _service->CreateSession(); 
    acceptEvent->SetSession( session );

    DWORD bytesReceived = 0;
    ExBool result = SocketUtil::AcceptEx( 
        _listener, 
        session->GetSocket(), 
        session->GetRecvBuffer(), 
        0, 
        sizeof( SOCKADDR_IN ) + 16, 
        sizeof( SOCKADDR_IN ) + 16, 
        OUT & bytesReceived, 
        static_cast<LPOVERLAPPED>( acceptEvent ) );

    if ( false == result )
    {
        const ExInt32 errorCode = ::WSAGetLastError();
        if ( errorCode != WSA_IO_PENDING )
        {
            _RegisterAccept( acceptEvent );
        }
    }
}

/**********************************************************************************************************************
 * @brief 연결 수락 처리를 수행한다.
**********************************************************************************************************************/
ExVoid Listener::_ProcessAccept( IocpAcceptEvent* acceptEvent )
{
    do
    {
        SessionPtr session = acceptEvent->GetSession();
        ExBool result = SocketUtil::SetUpdateAcceptSocket( session->GetSocket(), _listener );
        if ( false == result )
            break;

        SOCKADDR_IN sockAddress;
        ExInt32 sizeOfSockAddr = sizeof( sockAddress );
        if ( SOCKET_ERROR == ::getpeername(
            session->GetSocket(),
            OUT reinterpret_cast<SOCKADDR*>( &sockAddress ),
            &sizeOfSockAddr ) )
            break;

        session->SetNetAddress( NetAddress( sockAddress ) );
        session->_ProcessConnect();
        cout << "Client Connected!" << endl;

    } while ( false );
    
    _RegisterAccept( acceptEvent );
}

/**********************************************************************************************************************
* @file  Session.h
*
* @brief Session 클래스 h 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#pragma once


#include "IocpCore.h"
#include "IocpObject.h"
#include "IocpConnectEvent.h"
#include "IocpDisconnectEvent.h"
#include "IocpSendEvent.h"
#include "IocpRecvEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"


class Service;


/**********************************************************************************************************************
* @class Session
*
* @brief Session 처리 클래스
**********************************************************************************************************************/
class Session : public IocpObject
{
    friend class Listener;
    friend class IocpCore;
    friend class Service;

private:
    /// 소켓
    SOCKET _socket = INVALID_SOCKET;

    /// 서비스
    ExWeakPtr< Service > _service;

    /// 네트워크 주소
    NetAddress _netAddress = {};

    /// 커넥션 여부
    ExAtomic< ExBool > _connected = false;

private:
    USE_LOCK;
   
    /// 수신 버퍼
    RecvBuffer _recvBuffer;

    /// 송신 버퍼 큐
    std::queue< SendBufferPtr > _sendQueu;

    /// Send 등록 여부
    ExAtomic< ExBool > _sendRegistered = false;

    /// ConnectEvent
    IocpConnectEvent _connectEvent;

    /// DisconnectEvent
    IocpDisconnectEvent _disconnectEvent;

    /// RecvEvent
    IocpRecvEvent _recvEvent;

    /// SendEvent
    IocpSendEvent _sendEvent;
    
public:
    /// 생성자
    Session();
    
    /// 소멸자
    virtual ~Session();

public:
    /// 송신 한다
    ExVoid Send( const SendBufferPtr& sendBuffer );

    /// 연결 한다
    ExBool Connect();

    /// 연결을 끊는다
    ExVoid Disconnect( const WCHAR* cause );

    /// 커넥션 여부를 반환한다
    ExBool IsConnected() { return _connected; }

public:
    /// 핸들러를 반환한다
    virtual HANDLE GetHandle() override;

    /// 처리한다.
    virtual void Dispatch( class IocpEvent* iocpEvent, ExInt32 numOfBytes = 0 ) override;

public:
    /// 소켓을 반환한다
    SOCKET GetSocket() { return _socket; }

    /// 서비스를 반환한다
    ExSharedPtr< Service > GetService() { return _service.lock(); }

    /// 네트워크 주소를 반환한다
    NetAddress GetAddress() { return _netAddress; }

    /// 수신 버퍼를 반환한다
    RecvBuffer& GetRecvBuffer() { return _recvBuffer; }

    /// 세션을 반환한다
    SessionPtr GetSessionPtr() { return static_pointer_cast<Session>( shared_from_this() ); }

    /// 네트워크 주소를 설정한다.
    ExVoid SetNetAddress( NetAddress netAddress );

    /// 서비스를 설정한다
    ExVoid SetService( const ExSharedPtr< Service >& service ) { _service = service; }

protected:
    /// 연결 되었을 때 처리한다
    virtual ExVoid OnConnected();

    /// 연결이 끊어졌을 때 처리한다
    virtual ExVoid OnDisconnected();

    /// 데이터가 송신되었을 때 처리한다
    virtual ExVoid OnSent( ExInt32 len );

    /// 데이터가 수신되었을 때 처리한다
    virtual ExInt32 OnReceived( BYTE* buffer, ExInt32 len );

private:
    /// 연결을 등록한다
    ExBool _RegisterConnect();

    /// 연결 종료를 등록한다.
    ExBool _RegisterDisconnect();

    /// 수신을 등록한다
    ExVoid _RegisterRecv();

    /// 송신을 등록한다
    ExVoid _RegisterSend();

    /// 연결을 수행한다
    ExVoid _ProcessConnect();

    /// 연결 종료를 수행한다
    ExVoid _ProcessDisconnect();
    
    /// 수신을 수행한다
    ExVoid _ProcessRecv( ExInt32 numOfBytes );
    
    /// 송신을 수행한다
    ExVoid _ProcessSend( ExInt32 numOfBytes );

    /// 핸들 에러를 처리한다
    ExVoid _HandleError( ExInt32 errorCode );
};


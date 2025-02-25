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
#include "NetAddress.h"


/**********************************************************************************************************************
* @class Session
*
* @brief Session 처리 클래스
**********************************************************************************************************************/
class Session : public IocpObject
{
private:
	/// 소켓
	SOCKET _socket = INVALID_SOCKET;

	/// 네트워크 주소
	NetAddress _netAddress = {};

	/// 커넥션 여부
	ExAtomic< ExBool > _connected = false;

	/// 수신 버퍼 (임시)
	char _recvBuffer[ 1000 ] = {};

public:
	/// 생성자
	Session();
	
	/// 소멸자
	virtual ~Session();

public:
	/// 네트워크 주소를 반환한다.
	NetAddress GetAddress() { return _netAddress; }

	/// 소켓을 반환한다.
	SOCKET GetSocket() { return _socket; }

	/// 수신 버퍼를 반환한다.
	char* GetRecvBuffer() { return _recvBuffer; }

	/// 네트워크 주소를 설정한다.
	ExVoid SetNetAddress( NetAddress netAddress );

public:
	/// 핸들러를 반환한다.
	virtual HANDLE GetHandle() override;

	/// 처리한다.
	virtual void Dispatch( class IocpEvent* iocpEvent, ExInt32 numOfBytes = 0 ) override;
};


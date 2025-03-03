/**********************************************************************************************************************
* @file  Listener.h
*
* @brief Listener 클래스 h 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#pragma once


#include "IocpObject.h"
#include "IocpAcceptEvent.h"
#include "NetAddress.h"


/**********************************************************************************************************************
* @class Listener
*
* @brief Listener 처리 클래스
**********************************************************************************************************************/
class Listener : public IocpObject
{
public:
	/// IocpAcceptEvent 리스트 타입 정의
	using IocpAcceptEventList = std::vector< IocpAcceptEvent* >;

private:
	/// 소켓
	SOCKET _listener = INVALID_SOCKET;

	/// IocpAcceptEvent 리스트
	IocpAcceptEventList _iocpAcceptEventList;

	/// 서비스
	ServerServicePtr _service;

public:
	/// 생성자
	Listener() = default;
	
	/// 소멸자
	~Listener();

public:
	/// 연결 수락을 시작한다
	ExBool StartAccept( ServerServicePtr service );

	/// 소켓을 종료한다.
	ExVoid CloseSocket();

/// IocpObject
public:
	/// 핸들러를 반환한다.
	virtual HANDLE GetHandle() override;

	/// 처리한다.
	virtual void Dispatch( class IocpEvent* iocpEvent, ExInt32 numOfBytes = 0 ) override;

private:
	/// 연결 수락 이벤트를 등록한다.
	ExVoid _RegisterAccept( IocpAcceptEvent* acceptEvent );

	/// 연결 수락 처리를 수행한다.
	ExVoid _ProcessAccept( IocpAcceptEvent* acceptEvent );
};

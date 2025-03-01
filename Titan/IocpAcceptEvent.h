/**********************************************************************************************************************
* @file  IocpAcceptEvent.h
*
* @brief IocpAcceptEvent 클래스 h 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#pragma once


#include "IocpEvent.h"


class Session;


/**********************************************************************************************************************
* @class IocpAcceptEvent
*
* @brief IocpAcceptEvent 처리 클래스
**********************************************************************************************************************/
class IocpAcceptEvent : public IocpEvent
{
private:
	/// 세션
	SessionPtr _session = nullptr;

public:
	/// 생성자
	IocpAcceptEvent();

	/// 소멸자
	~IocpAcceptEvent() = default;

public:
	/// 세션을 반환합니다.
	const SessionPtr& GetSession() { return _session; }

	/// 세션을 설정합니다.
	ExVoid SetSession( const SessionPtr& session ) { _session = session; }
};

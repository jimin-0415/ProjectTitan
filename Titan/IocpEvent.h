/**********************************************************************************************************************
* @file  IocpEvent.h
*
* @brief IocpEvent 클래스 h 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#pragma once


#include "EnumTypes.h"


/**********************************************************************************************************************
* @class IocpEvent
*
* @brief IocpEvent 클래스 (Overlapped)
**********************************************************************************************************************/
class IocpEvent : public OVERLAPPED
{
protected:
	/// Iocp 이벤트 타입
	EIocpEventType _type;

	/// Iocp 오브젝트
	IocpObjectPtr _owner;

public:
	/// 생성자
	IocpEvent( EIocpEventType iocpEventType );

	/// 소멸자
	~IocpEvent() = default;

public:
	/// 개체를 초기화한다.
	ExVoid Clear();

public:
	/// IocpEventType 을 반환한다.
	EIocpEventType GetType() { return _type; }

	/// Owner 를 반환한다.
	const IocpObjectPtr& GetOwner() { return _owner; }

	/// Owner 를 세팅한다.
	ExVoid SetOwner( const IocpObjectPtr& owner ) { _owner = owner; }
};

static_assert( !std::is_polymorphic<IocpEvent>::value, "Error: The class IocpEvent cannot have virtual functions or a vtable." );
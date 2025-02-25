/**********************************************************************************************************************
* @file  IocpEvent.cpp
*
* @brief IocpEvent 클래스 cpp 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#include "pch.h"
#include "IocpEvent.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
IocpEvent::IocpEvent( EIocpEventType iocpEventType )
:
_type( iocpEventType )
{
	Clear();
}

/**********************************************************************************************************************
* @brief 개체를 초기화 합니다.
**********************************************************************************************************************/
ExVoid IocpEvent::Clear()
{
	/*OVERLAPPED::hEvent     = 0;
	OVERLAPPED::Internal     = 0;
	OVERLAPPED::InternalHigh = 0;
	OVERLAPPED::Offset       = 0;
	OVERLAPPED::OffsetHigh   = 0;*/

	::ZeroMemory( this, sizeof( OVERLAPPED ) );
}

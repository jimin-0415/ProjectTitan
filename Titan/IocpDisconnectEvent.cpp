/**********************************************************************************************************************
* @file  IocpDisconnectEvent.cpp
*
* @brief IocpDisconnectEvent 클래스 cpp 파일
*
* @date  2025.03.02
**********************************************************************************************************************/


#include "pch.h"
#include "IocpDisconnectEvent.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
IocpDisconnectEvent::IocpDisconnectEvent()
:
IocpEvent( EIocpEventType::Disconnect )
{
}

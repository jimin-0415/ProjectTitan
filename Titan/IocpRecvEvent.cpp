/**********************************************************************************************************************
* @file  IocpRecvEvent.cpp
*
* @brief IocpRecvEvent 클래스 cpp 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#include "pch.h"
#include "IocpRecvEvent.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
IocpRecvEvent::IocpRecvEvent()
:
IocpEvent( EIocpEventType::Recv)
{
}

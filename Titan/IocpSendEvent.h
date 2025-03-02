/**********************************************************************************************************************
* @file  IocpSendEvent.h
*
* @brief IocpSendEvent 클래스 h 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#pragma once


#include "IocpEvent.h"


/**********************************************************************************************************************
* @class IocpSendEvent
*
* @brief IocpSendEvent 처리 클래스
**********************************************************************************************************************/
class IocpSendEvent : public IocpEvent
{
public:
	/// 생성자
	IocpSendEvent();

	/// 소멸자
	~IocpSendEvent() = default;

public:
	/// TEMP SendBuffer
	std::vector<BYTE> Buffer;
};

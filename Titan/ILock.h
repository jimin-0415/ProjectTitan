/**********************************************************************************************************************
* @file  ILock.h
*
* @brief ILock h 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#pragma once


#include "CorePch.h"


/**********************************************************************************************************************
* @class ILock
*
* @brief Lock 인터페이스 
**********************************************************************************************************************/
class ILock : public Noncopyable
{
public:
	/// 잠금
	virtual void Lock()   = 0;
	
	/// 해제
	virtual void Unlock() = 0;
};

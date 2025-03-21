/**********************************************************************************************************************
* @file  WriteLockGuard.cpp
*
* @brief WriteLockGuard 클래스 cpp 파일
*
* @date  2025.02.20
**********************************************************************************************************************/


#include "pch.h"
#include "WriteLockGuard.h"
#include "RWSpinLock.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
WriteLockGuard::WriteLockGuard( RWSpinLock& lock )
:
_lock( lock )
{
	_lock.WriteLock();
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
WriteLockGuard::~WriteLockGuard()
{
	_lock.WriteUnlock();
}

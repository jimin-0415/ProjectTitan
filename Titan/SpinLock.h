/**********************************************************************************************************************
* @file  SpinLock.h
*
* @brief SpinLock 클래스 h 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#pragma once


#include "Types.h"
#include "LockType.h"


/**********************************************************************************************************************
* @class SpinLock
*
* @brief SpinLock 클래스
**********************************************************************************************************************/
class SpinLock : public ILock
{
private:
	/// 락
	ExAtomic< ExUInt32 > _lock;

public:
	/// 생성자
	SpinLock();

	/// 소멸자
	~SpinLock();

public:
	/// 잠금
	virtual void Lock() override;

	/// 해제
	virtual void Unlock() override;
};




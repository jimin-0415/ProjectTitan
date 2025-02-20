/**********************************************************************************************************************
* @file  RWSpinLock.cpp
*
* @brief RWSpinLock 클래스 cpp 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#include "pch.h"
#include "RWSpinLock.h"
#include "CoreTLS.h"


/**********************************************************************************************************************
* @brief 쓰기 잠금
**********************************************************************************************************************/
void RWSpinLock::WriteLock()
{
	const ExUInt32 lockThreadId = ( _lockFlag.load() & WriteMask ) >> 16;
	if ( LThreadId == lockThreadId )
	{
		// 동일 쓰레드 일 경우.
		_writeCount++;
		return;
	}

	// 아무도 소유 및 공유하지 않을때 경합해서 소유권 얻는다.
	const ExInt64 beginTick = ::GetTickCount64();
	const ExUInt32 desired = ( ( LThreadId << 16 ) & WriteMask );
	while ( true )
	{
		for ( ExUInt32 spinCount = 0; spinCount < MaxSpinCount; spinCount++ )
		{
			ExUInt32 expected = EmptyMask;
			if ( _lockFlag.compare_exchange_strong( OUT expected, desired ) )
			{
				_writeCount++;
				return;
			}
		}

		// check timeout
		if ( ::GetTickCount64() - beginTick >= AcquireTimeOutTick )
			CRASH( "LOCK_TIMEOUT!!!" );

		this_thread::yield();
	}
}

/**********************************************************************************************************************
* @brief 쓰기 잠금 해제
**********************************************************************************************************************/
void RWSpinLock::WriteUnlock()
{
	// ReadLock 다 풀기 전에 WriteUnlock 불가능.
	// R -> R (o)
	// R -> W (x)
	// W -> R (o)
	// w -> w (o)

	if ( ( _lockFlag.load() & ReadMask ) != 0 )
		CRASH( "Invalid Unlock Order!!" );

	const ExInt32 lockCount = --_writeCount;
	if ( 0 == lockCount )
		_lockFlag.store( EmptyMask );
}

/**********************************************************************************************************************
* @brief 읽기 잠금
**********************************************************************************************************************/
void RWSpinLock::ReadLock()
{
	// 동일한 쓰레드가 소유한다면 성공.
	const ExUInt32 lockThreadId = ( _lockFlag.load() & WriteMask ) >> 16;
	if ( LThreadId == lockThreadId )
	{
		// 동일 쓰레드 일 경우.
		_lockFlag.fetch_add( 1 );
		return;
	}

	// 아무도 소유하고 있지 않을(라이트 불가) 경우 경합해서 공유 카운트 증가.
	const ExInt64 beginTick = ::GetTickCount64();
	while ( true )
	{
		for ( ExUInt32 spinCount = 0; spinCount < MaxSpinCount; spinCount++ )
		{
			ExUInt32 expected = ( _lockFlag.load() & ReadMask );
			if ( _lockFlag.compare_exchange_strong( OUT expected, expected + 1 ) )
				return;
		}

		// check timeout
		if ( ::GetTickCount64() - beginTick >= AcquireTimeOutTick )
			CRASH( "LOCK_TIMEOUT!!!" );

		this_thread::yield();
	}
}

/**********************************************************************************************************************
* @brief 읽기 잠금 해제
**********************************************************************************************************************/
void RWSpinLock::ReadUnlock()
{
	// fetch_sub 하기전 값이 0일경우아.
	if ( ( _lockFlag.fetch_sub( 1 ) & ReadMask ) == 0 )
		CRASH( "Multiple Unlock!!" );
}

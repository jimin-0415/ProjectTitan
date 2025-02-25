/**********************************************************************************************************************
* @file  ThreadManager.cpp
*
* @brief ThreadManager 클래스 cpp 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#include "pch.h"
#include "ThreadManager.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
ThreadManager::ThreadManager()
{
	InitTLS();
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
ThreadManager::~ThreadManager()
{
}

/**********************************************************************************************************************
* @brief 새로운 쓰레드를 생성하고 실행합니다.
**********************************************************************************************************************/
void ThreadManager::Launch(Callback callback)
{
	ExLockGuard< ExMutex > lockGuard( _lock );

	_threadList.push_back(
		thread( 
			[=](){
					InitTLS();
					callback();
					DestroyTLS();
				 }
			) );
}

/**********************************************************************************************************************
* @brief 모든 스레드를 대기하고 종료를 기다립니다.
**********************************************************************************************************************/
void ThreadManager::Join()
{
	for ( thread& t : _threadList )
	{
		if ( t.joinable() )
			t.join();
	}

	_threadList.clear();
}

/**********************************************************************************************************************
* @brief TLS 개체를 초기화합니다.
**********************************************************************************************************************/
void ThreadManager::InitTLS()
{
	static ExAtomic<ExUInt32> sThreadId = 1;
	LThreadId = sThreadId.fetch_add( 1 );
}

/**********************************************************************************************************************
* @brief TLS 개체를 파괴합니다.
**********************************************************************************************************************/
void ThreadManager::DestroyTLS()
{
	// TLS 해제를 위한 추가 작업이 필요한 경우 구현
}

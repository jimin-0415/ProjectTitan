/**********************************************************************************************************************
* @file  ThreadManager.h
*
* @brief ThreadManager 클래스 h 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#pragma once


#include <functional>
#include <thread>


/**********************************************************************************************************************
* @class ThreadManager
*
* @brief Thread 관리 클래스
**********************************************************************************************************************/
class ThreadManager
{
private:
	/// 쓰레드 리스트 타입 정의
	using ThreadList = std::vector< thread >;

	/// 콜백 타입 정의
	using Callback = std::function< void(void) >;

private:
	/// 뮤텍스 락
	ExMutex _lock;

	/// 쓰레드 리스트
	ThreadList _threadList;

public:
	/// 생성자
	ThreadManager();
	
	/// 소멸자
	~ThreadManager();

public:
	/// 새로운 쓰레드를 생성하고 실행합니다.
	void Lauch( Callback callback );
	
	/// 모든 스레드를 대기하고 종료를 기다립니다.
	void Join();

public:
	/// TLS 개체를 초기화합니다.
	static void InitTLS();

	/// TLS 개체를 파괴합니다.
	static void DestroyTLS();
};


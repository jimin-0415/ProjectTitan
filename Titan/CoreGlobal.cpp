/**********************************************************************************************************************
* @file  CoreGlobal.cpp
*
* @brief CoreGlobal 클래스 cpp 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#include "pch.h"
#include "CoreGlobal.h"
#include "SocketUtil.h"
#include "ThreadManager.h"
#include "SendBufferManager.h"


/// CoreGlobal 전역 개체
CoreGlobal GCoreGlobal;

/// 쓰레드 관리자 전역 개체
ThreadManager* GThreadManager = nullptr;

/// 송신 버퍼 관리자 전역 개체
SendBufferManager* GSendBufferManager = nullptr;


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
CoreGlobal::CoreGlobal()
{
	/// 초기화 순서로 CoreGlobal 에서 전역 개체 관리
	GThreadManager     = new ThreadManager();
	GSendBufferManager = new SendBufferManager();

	SocketUtil::Init();
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
CoreGlobal::~CoreGlobal()
{
	delete GThreadManager;
	delete GSendBufferManager;

	SocketUtil::Clear();
}

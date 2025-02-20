/**********************************************************************************************************************
* @file  CoreGlobal.cpp
*
* @brief CoreGlobal 클래스 cpp 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"


ThreadManager* GThreadManager = nullptr;


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
CoreGlobal::CoreGlobal()
{
	/// 초기화 순서로 CoreGlobal 에서 전역 개체 관리
	GThreadManager = new ThreadManager();
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
CoreGlobal::~CoreGlobal()
{
	delete GThreadManager;
}

CoreGlobal GCoreGlobal;
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


/// 쓰레드 매니져
ThreadManager* GThreadManager = nullptr;


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
CoreGlobal::CoreGlobal()
{
	GThreadManager = new ThreadManager();
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
CoreGlobal::~CoreGlobal()
{
	delete GThreadManager;
}

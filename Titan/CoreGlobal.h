/**********************************************************************************************************************
* @file  CoreGlobal.h
*
* @brief CoreGlobal 클래스 h 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#pragma once


/// 쓰레드 관리자 전역 개체
extern class ThreadManager* GThreadManager;

/// 송신 버퍼 관리자 전역 개체
extern class SendBufferManager* GSendBufferManager;


/**********************************************************************************************************************
* @class CoreGlobal
*
* @brief 전역 개체 클래스
**********************************************************************************************************************/
class CoreGlobal
{
public:
	/// 생성자
	CoreGlobal();

	/// 소멸자
	~CoreGlobal();
};

/// CoreGlobal 전역 개체
extern CoreGlobal GCoreGlobal;

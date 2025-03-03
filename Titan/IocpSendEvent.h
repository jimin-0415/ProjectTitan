/**********************************************************************************************************************
* @file  IocpSendEvent.h
*
* @brief IocpSendEvent 클래스 h 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#pragma once


#include "IocpEvent.h"


/**********************************************************************************************************************
* @class IocpSendEvent
*
* @brief IocpSendEvent 처리 클래스
**********************************************************************************************************************/
class IocpSendEvent : public IocpEvent
{
private:
	/// 송신 버퍼 벡터 타입 정의
	using SendBufferVector = std::vector< SendBufferPtr >;

private:
	/// 송신 버퍼 리스트
	SendBufferVector _sendBufferVector;

public:
	/// 생성자
	IocpSendEvent();

	/// 소멸자
	~IocpSendEvent() = default;

public:
	/// 송신 버퍼에 추가한다
	ExVoid AddBuffer( const SendBufferPtr& sendBuffer );

	/// 버퍼를 초기화한다
	ExVoid ClearBuffer();

public:
	/// 송신 버퍼 벡터를 반환한다
	const SendBufferVector& GetSendBufferVector() { return _sendBufferVector; }
};

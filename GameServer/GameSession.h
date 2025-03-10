/**********************************************************************************************************************
* @file  GameSession.h
*
* @brief GameSession 클래스 h 파일
*
* @date  2025.03.03
**********************************************************************************************************************/


#pragma once


#include "PacketSession.h"


/**********************************************************************************************************************
* @class GameSession
*
* @brief GameSession 클래스
**********************************************************************************************************************/
class GameSession : public PacketSession
{
public:
    /// 생성자
    GameSession();
    
    /// 소멸자
    virtual ~GameSession();

public:
    /// 연결 되었을 때 처리한다
    virtual ExVoid OnConnected() override final;

    /// 연결이 끊어졌을 때 처리한다
    virtual ExVoid OnDisconnected() override final;

    /// 데이터가 송신되었을 때 처리한다
    virtual ExVoid OnSent( ExInt32 len ) override final;

    /// 데이터가 수신되었을 때 처리한다
    virtual ExVoid OnReceivedPacket( BYTE* buffer, ExInt32 len ) override final;
};
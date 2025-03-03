/**********************************************************************************************************************
* @file  GameSessionMaanger.h
*
* @brief GameSessionMaanger 클래스 h 파일
*
* @date  2025.03.03
**********************************************************************************************************************/


#pragma once


class GameSession;


/**********************************************************************************************************************
* @class GameSessionMaanger
*
* @brief GameSessionMaanger 클래스
**********************************************************************************************************************/
class GameSessionMaanger
{
public:
    /// 게인 세션 쉐어드 타입 정의
    using GameSessionPtr = ExSharedPtr< GameSession >;

    /// 게임 세션 셋 타입 정의
    using GameSessionSet = std::set< GameSessionPtr >;

private:
    USE_LOCK;

    /// 게임 세션 셋
    GameSessionSet _sessionSet;

public:
    /// 추가한다
    ExVoid Add( GameSessionPtr session );

    /// 제거한다
    ExVoid Remove( GameSessionPtr session );

    /// 브로드캐스트 한다
    ExVoid Broadcast( SendBufferPtr sendBuffer );
};

extern GameSessionMaanger GSessionManager;
/**********************************************************************************************************************
* @file  GameSession.cpp
*
* @brief GameSession 클래스 cpp 파일
*
* @date  2025.03.03
**********************************************************************************************************************/


#include "pch.h"
#include "GameSession.h"
#include "CoreGlobal.h"
#include "GameSessionMaanger.h"
#include "SendBuffer.h"
#include "SendBufferManager.h"
#include "ServerPacketHandler.h"
#include "Types.h"

/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
GameSession::GameSession()
{
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
GameSession::~GameSession()
{
    cout << "Release GameSession!!!" << endl;
}

/**********************************************************************************************************************
* @brief 연결 되었을 때 처리한다
**********************************************************************************************************************/
ExVoid GameSession::OnConnected()
{
    GSessionManager.Add( static_pointer_cast<GameSession>( shared_from_this() ) );
}

/**********************************************************************************************************************
* @brief 연결이 끊어졌을 때 처리한다
**********************************************************************************************************************/
ExVoid GameSession::OnDisconnected()
{
    GSessionManager.Remove( static_pointer_cast<GameSession>( shared_from_this() ) );
}

/**********************************************************************************************************************
* @brief 데이터가 송신되었을 때 처리한다
**********************************************************************************************************************/
ExVoid GameSession::OnSent( ExInt32 len )
{
    cout << "Server OnSend Len = " << len << endl;
}

/**********************************************************************************************************************
* @brief 데이터가 수신되었을 때 처리한다
**********************************************************************************************************************/
ExVoid GameSession::OnReceivedPacket( BYTE* buffer, ExInt32 len )
{
    ServerPacketHandler::HandlerPacket( buffer, len );
}

/**********************************************************************************************************************
* @file  PacketSession.h
*
* @brief PacketSession 클래스 h 파일
*
* @date  2025.03.05
**********************************************************************************************************************/


#pragma once


#include "Session.h"


/**********************************************************************************************************************
* @class PacketSession
*
* @brief PacketSession 각주
**********************************************************************************************************************/
class PacketSession : public Session
{
public:
    PacketSession();
    ~PacketSession();

    PacketSessionPtr GetPacketSessionPtr() { return static_pointer_cast<PacketSession>( shared_from_this() ); }

protected:
    /// 수신되었을 때 처리한다
    virtual ExInt32 OnReceived( BYTE* buffer, ExInt32 len ) final;

    /// 패킷 수신되었을 때 처리한다
    virtual ExVoid OnReceivedPacket( BYTE* buffer, ExInt32 len ) abstract;
};

// 임시 패킷 헤더 파일
struct PacketHeader
{
    ExInt16 size;
    ExInt16 id;
};
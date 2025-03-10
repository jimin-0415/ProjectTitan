/**********************************************************************************************************************
* @file  ClientPacketHandler.h
*
* @brief ClientPacketHandler 클래스 h 파일
*
* @date  2025.03.10
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class ClientPacketHandler
*
* @brief ClientPacketHandler 클래스
**********************************************************************************************************************/
class ClientPacketHandler
{
public:
    /// 패킷을 처리한다
    static ExVoid HandlerPacket( BYTE* buffer, ExInt32 len );

    /// S_Test 패킷을 처리한다
    static ExVoid Handle_S_Test( BYTE* buffer, ExInt32 len );
};

// 임시
struct S_TEST
{
    ExUInt64 id;
    ExUInt32 hp;
    ExUInt16 attack;
};
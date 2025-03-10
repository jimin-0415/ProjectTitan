/**********************************************************************************************************************
* @file  ServerPacketHandler.cpp
*
* @brief ServerPacketHandler 클래스 cpp 파일
*
* @date  2025.03.10
**********************************************************************************************************************/


#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "PacketSession.h"
#include "BufferWriter.h"
#include "SendBuffer.h"
#include "SendBufferManager.h"


/**********************************************************************************************************************
* @brief 패킷을 처리한다
**********************************************************************************************************************/
ExVoid ServerPacketHandler::HandlerPacket( BYTE* buffer, ExInt32 len )
{
    BufferReader br( buffer, len );

    PacketHeader header;
    br.Peek( &header );

    switch ( header.id )
    {
    default:
        break;
    }
    
    return ExVoid();
}

/**********************************************************************************************************************
* @brief 송신 버퍼를 생성한다
**********************************************************************************************************************/
SendBufferPtr ServerPacketHandler::MakeSendBuffer( Protocol::S_TEST& pkt )
{
    return _MakeSendBuffer( pkt, ExUInt16( EProtocol::S_TEST ) );
}

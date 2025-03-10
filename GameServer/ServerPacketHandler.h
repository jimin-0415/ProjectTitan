/**********************************************************************************************************************
* @file  ServerPacketHandler.h
*
* @brief ServerPacketHandler 클래스 h 파일
*
* @date  2025.03.10
**********************************************************************************************************************/


#pragma once


#include "Protocol.pb.h"
#include "PacketSession.h"
#include "SendBufferManager.h"


/**********************************************************************************************************************
* @class ServerPacketHandler
*
* @brief ServerPacketHandler 클래스
**********************************************************************************************************************/
class ServerPacketHandler
{
public:
	/// 패킷을 처리한다
    static ExVoid HandlerPacket( BYTE* buffer, ExInt32 len );
	
	/// 송신 버퍼를 생성한다
    static SendBufferPtr MakeSendBuffer( Protocol::S_TEST& pkt );
};

/**********************************************************************************************************************
* @brief 송신 버퍼를 생성한다
**********************************************************************************************************************/
template<typename T>
SendBufferPtr _MakeSendBuffer( T& pkt, ExUInt16 pktId )
{
	const ExUInt16 dataSize = static_cast<ExUInt16>( pkt.ByteSizeLong() );
	const ExUInt16 packetSize = dataSize + sizeof( PacketHeader );

	SendBufferPtr sendBuffer = GSendBufferManager->Open( packetSize );
	PacketHeader* header = reinterpret_cast<PacketHeader*>( sendBuffer->GetBuffer() );
	header->size = packetSize;
	header->id = pktId;
	ASSERT_CRASH( pkt.SerializeToArray( &header[ 1 ], dataSize ) );
	sendBuffer->Close( packetSize );

	return sendBuffer;
}
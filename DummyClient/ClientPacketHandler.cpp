/**********************************************************************************************************************
* @file  ClientPacketHandler.cpp
*
* @brief ClientPacketHandler 클래스 cpp 파일
*
* @date  2025.03.10
**********************************************************************************************************************/


#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "PacketSession.h"
#include "Protocol.pb.h"


/**********************************************************************************************************************
* @brief 패킷을 처리한다
**********************************************************************************************************************/
ExVoid ClientPacketHandler::HandlerPacket( BYTE* buffer, ExInt32 len )
{
    BufferReader br( buffer, len );

    PacketHeader header;
    br >> header;

    switch ( (EProtocol)header.id )
    {
    case EProtocol::S_TEST: Handle_S_Test( buffer, len ); break;
    }
}

/**********************************************************************************************************************
* @brief 송신 버퍼를 생성한다
**********************************************************************************************************************/
ExVoid ClientPacketHandler::Handle_S_Test( BYTE* buffer, ExInt32 len )
{
	Protocol::S_TEST pkt;

	ASSERT_CRASH( pkt.ParseFromArray( buffer + sizeof( PacketHeader ), len - sizeof( PacketHeader ) ) );

	cout << pkt.id() << " " << pkt.hp() << " " << pkt.attack() << endl;

	cout << "BUFSIZE : " << pkt.buffs_size() << endl;

	for ( auto& buf : pkt.buffs() )
	{
		cout << "BUFINFO : " << buf.buffid() << " " << buf.remiantime() << endl;
		cout << "VICTIMS : " << buf.victims_size() << endl;
		for ( auto& vic : buf.victims() )
		{
			cout << vic << " ";
		}

		cout << endl;
	}
}

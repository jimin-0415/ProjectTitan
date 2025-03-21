/**********************************************************************************************************************
* @file  PacketSession.cpp
*
* @brief PacketSession 클래스 cpp 파일
*
* @date  2025.03.05
**********************************************************************************************************************/


#include "pch.h"
#include "PacketSession.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
PacketSession::PacketSession()
{
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
PacketSession::~PacketSession()
{
}

/**********************************************************************************************************************
* @brief 수신되었을 때 처리한다
**********************************************************************************************************************/
ExInt32 PacketSession::OnReceived( BYTE* buffer, ExInt32 len )
{
    ExInt32 processLen = 0;
    while ( true )
    {
        ExInt32 dataSize = len - processLen;
        if ( dataSize < sizeof( PacketHeader ) )
            break;

        //PacketHeader header = *( (PacketHeader*) &buffer[ 0 ] );
        PacketHeader header = *( reinterpret_cast<PacketHeader*>( &buffer[ processLen ] ) );
        if ( dataSize < header.size )
            break;

        // 패킷 조립 성공
        OnReceivedPacket( &buffer[ processLen  ], header.size );

        processLen += header.size;
    }

    return processLen;
}

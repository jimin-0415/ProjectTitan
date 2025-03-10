/**********************************************************************************************************************
* @file  GameServer.cpp
*
* @brief 프로그램 실행 시작 파일
*
* @date  2025.02.15
**********************************************************************************************************************/


#include "pch.h"
#include "BufferWriter.h"
#include "ThreadManager.h"
#include "ServerService.h"
#include "GameSession.h"
#include "SendBuffer.h"
#include "SendBufferManager.h"
#include "ServerPacketHandler.h"
#include "GameSessionMaanger.h"
#include "Protocol.pb.h"


template< typename T >
std::shared_ptr< T > SessionFactory()
{
    return std::make_shared<T>();
}

/**********************************************************************************************************************
* @brief 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
**********************************************************************************************************************/
int main()
{
    ServerServicePtr service = std::make_shared<ServerService>(
        NetAddress( L"127.0.0.1", 7777 ),
        std::make_shared<IocpCore>(),
        SessionFactory< GameSession >, // TODO : SessionManager 등
        100 );

    ASSERT_CRASH( service->Start() );
    for ( ExInt32 i = 0; i < 5; i++ )
    {
        GThreadManager->Launch( [ = ]()
        {
            while ( true )
            {
                service->GetIocpCore()->Dispatch();
            }
        } );
    }

    char sendData[ 1000] = "Hello World !!";

    while ( true )
    {
        Protocol::S_TEST pkt;
        pkt.set_id( 1000 );
        pkt.set_hp( 100 );
        pkt.set_attack( 10 );

        {
            Protocol::BuffData* buff = pkt.add_buffs();
            buff->set_buffid( 100 );
            buff->set_remiantime( 1.2f );
            buff->add_victims( 4000 );
            buff->add_victims( 500 );
        }
        
        {
            Protocol::BuffData* buff = pkt.add_buffs();
            buff->set_buffid( 200 );
            buff->set_remiantime( 2.2f );
            buff->add_victims( 7000 );
            buff->add_victims( 800 );
        }

        
        SendBufferPtr sendBuffer = ServerPacketHandler::MakeSendBuffer( pkt );
        GSessionManager.Broadcast( sendBuffer );

        this_thread::sleep_for( 500ms );
    }

    GThreadManager->Join();
}

/**********************************************************************************************************************
* @file  GameServer.cpp
*
* @brief 프로그램 실행 시작 파일
*
* @date  2025.02.15
**********************************************************************************************************************/


#include "pch.h"
#include "ThreadManager.h"
#include "ServerService.h"
#include "GameSession.h"
#include "SendBuffer.h"
#include "SendBufferManager.h"
#include "GameSessionMaanger.h"


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

    char SendData[ 1000] = "Hello World !!";

    while ( true )
    {
        SendBufferPtr sendBuffer = GSendBufferManager->Open( 4096 );

        BYTE* buffer = sendBuffer->GetBuffer();
        reinterpret_cast<PacketHeader*>( buffer )->id = 1;
        reinterpret_cast<PacketHeader*>( buffer )->size = ( sizeof( SendData ) + sizeof( PacketHeader ) );
        
        ::memcpy( &buffer[ 4 ], buffer, sizeof( SendData ) );
        sendBuffer->Close( sizeof( SendData ) + sizeof( PacketHeader ) );

        GSessionManager.Broadcast( sendBuffer );

        this_thread::sleep_for( 500ms );
    }

    GThreadManager->Join();
}

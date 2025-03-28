/**********************************************************************************************************************
* @file  DummyClient.cpp
*
* @brief 프로그램 실행 시작 파일
*
* @date  2025.02.15
**********************************************************************************************************************/


#include "pch.h"
#include "BufferReader.h"
#include "ClientService.h"
#include "ClientPacketHandler.h"
#include "PacketSession.h"
#include "SendBuffer.h"
#include "SendBufferManager.h"
#include "ThreadManager.h"


char sendData[] = "Hello World!";


template< typename T >
std::shared_ptr< T > SessionFactory()
{
    return std::make_shared<T>();
}


class GameServerSession : public PacketSession
{
public:
    ~GameServerSession()
    {
        cout << "~ServerSession" << endl;
    }

    virtual void OnConnected() override final
    {
        cout << "Connected To Server " << endl;
        /*SendBufferPtr sendBuffer = GSendBufferManager->Open( 4096 );
        ::memcpy( sendBuffer->GetBuffer(), sendData, sizeof( sendData ) );
        sendBuffer->Close( sizeof( sendData ) );

        Send( sendBuffer );*/
    }

    virtual void OnDisconnected() override final
    {
        //cout << "On Disconnected - DummyClient" << endl;
    }

    virtual ExVoid OnReceivedPacket( BYTE* buffer, ExInt32 len ) override final
    {
        ClientPacketHandler::HandlerPacket( buffer, len );
    }

    virtual ExVoid OnSent( ExInt32 len ) override final
    {
        //cout << "(더미)OnSend Len = " << len << endl;
    }
};

void HandleError( const char* cause )
{
	ExInt32 errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode : " << errCode << endl;
}


/**********************************************************************************************************************
* @brief 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
**********************************************************************************************************************/
int main()
{
    this_thread::sleep_for( 1s );

    ClientServicePtr service = std::make_shared<ClientService>(
        NetAddress( L"127.0.0.1", 7777 ),
        std::make_shared<IocpCore>(),
        SessionFactory< GameServerSession >, // TODO : SessionManager 등
        1 );

    ASSERT_CRASH( service->Start() );

    for ( ExInt32 i = 0; i < 2; i++ )
    {
        GThreadManager->Launch( [ = ]()
        {
            while ( true )
            {
                service->GetIocpCore()->Dispatch();
            }
        } );
    }

    GThreadManager->Join();
}

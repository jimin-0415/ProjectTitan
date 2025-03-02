/**********************************************************************************************************************
* @file  DummyClient.cpp
*
* @brief 프로그램 실행 시작 파일
*
* @date  2025.02.15
**********************************************************************************************************************/


#include "pch.h"
#include "ClientService.h"
#include "Session.h"
#include "ThreadManager.h"


char sendBuffer[] = "Hello World!";


template< typename T >
std::shared_ptr< T > SessionFactory()
{
    return std::make_shared<T>();
}


class GameServerSession : public Session
{
public:
    ~GameServerSession()
    {
        cout << "~ServerSession" << endl;
    }

    virtual void OnConnected() override final
    {
        cout << "Connected To Server " << endl;
        Send( (BYTE*) sendBuffer, sizeof( sendBuffer ) );
    }

    virtual void OnDisconnected() override final
    {
        cout << "On Disconnected - DummyClient" << endl;
    }

    virtual ExInt32 OnReceived( BYTE* buffer, ExInt32 len ) override final
    {
        cout << "OnRecv Len = " << len << endl;

        this_thread::sleep_for( 1s );

        Send( (BYTE*) sendBuffer, sizeof( sendBuffer ) );
        return len;
    }

    /// 데이터가 송신되었을 때 처리한다
    virtual ExVoid OnSent( ExInt32 len ) override final
    {
        cout << "OnSend Len = " << len << endl;
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
    this_thread::sleep_for( 5s );

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

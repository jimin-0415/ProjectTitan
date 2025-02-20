/**********************************************************************************************************************
* @file  GameServer.cpp
*
* @brief 프로그램 실행 시작 파일
*
* @date  2025.02.15
**********************************************************************************************************************/


#include "pch.h"
#include "ThreadManager.h"

class TestLock
{
private:
    USE_LOCK;

public:
    int TestRead()
    {
        READ_LOCK;

        if ( _queue.empty() )
            return -1;

        return _queue.front();
    }

    void TestPush()
    {
        WRITE_LOCK;

        _queue.push( rand() % 100 );
    }

    void TestPop()
    {
        WRITE_LOCK;

        if ( _queue.empty() == false )
            _queue.pop();
    }

public:
    queue<ExInt32> _queue;
};

TestLock testLock;

/**********************************************************************************************************************
* @brief Thread Main 테스트용 function
**********************************************************************************************************************/
void ThreadMain()
{
    while ( true )
    {
        testLock.TestPush();
        this_thread::sleep_for( 1s );
        testLock.TestPop();
    }
}

/**********************************************************************************************************************
* @brief Thread Main 테스트용 function
**********************************************************************************************************************/
void ThreadMain2()
{
    while ( true )
    {
        int value = testLock.TestRead();
        cout << value << endl;
        this_thread::sleep_for( 1ms );
    }
}

/**********************************************************************************************************************
* @brief 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
**********************************************************************************************************************/
int main()
{
    for ( ExInt32 i = 0; i < 2; i++ )
    {
        GThreadManager->Lauch( ThreadMain );
    }

    for ( ExInt32 i = 0; i < 5; i++ )
    {
        GThreadManager->Lauch( ThreadMain2 );
    }

    GThreadManager->Join();
}

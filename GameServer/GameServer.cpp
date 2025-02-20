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

class D : public TObjectBase
{
public:
    virtual void Test()
    {
        cout << "TestA" << endl;
    }

    void Test2()
    {
        cout << "TestA2" << endl;
    }
};

class A : public TObjectBase
{
public:
    virtual void Test()
    {
        cout << "TestA" << endl;
    }

    void Test2()
    {
        cout << "TestA2" << endl;
    }
};

class B : public A
{
public:
    virtual void Test() override
    {
        cout << "TestB" << endl;
    }

    void Test2()
    {
        cout << "TestB2" << endl;
    }
};

class C : public B
{
public:
    virtual void Test() override
    {
        cout << "TestC" << endl;
    }

    void Test2()
    {
        cout << "TestC2" << endl;
    }
};


/**********************************************************************************************************************
* @brief 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
**********************************************************************************************************************/
int main()
{
    A* a = new C();
    C* c = a->Cast<C>();
    C* c2 = dynamic_cast<C*>( a );

    B* b = a->Cast<B>();
    B* b2 = dynamic_cast<B*>( a );

    C* bc = b->Cast<C>();
    C* bc2 = dynamic_cast<C*>( b );

    D* d = a->Cast<D>();
    D* dc2 = dynamic_cast<D*>( a );
    /*d->Test();
    dc2->Test();*/

    c->Test();
    c2->Test();
    b->Test();
    b2->Test();
    bc->Test();
    bc2->Test();

    c->Test2();
    c2->Test2();
    b->Test2();
    b2->Test2();
    bc->Test2();
    bc2->Test2();

    //C* c = a->Cast<C>();
    //c->Test();

    /*for ( ExInt32 i = 0; i < 2; i++ )
    {
        GThreadManager->Lauch( ThreadMain );
    }

    for ( ExInt32 i = 0; i < 5; i++ )
    {
        GThreadManager->Lauch( ThreadMain2 );
    }

    GThreadManager->Join();*/
}

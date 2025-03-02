/**********************************************************************************************************************
* @file  ClientService.cpp
*
* @brief ClientService 클래스 cpp 파일
*
* @date  2025.02.28
**********************************************************************************************************************/


#include "pch.h"
#include "ClientService.h"
#include "Session.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
ClientService::ClientService( 
    NetAddress     targetAddress, 
    IocpCorePtr    iocpCore, 
    SessionFactory sessionFactory, 
    ExInt32        maxSessionCount )
:
Super( EServiceType::Client, targetAddress, iocpCore, sessionFactory, maxSessionCount )
{
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
ClientService::~ClientService()
{
}

/**********************************************************************************************************************
* @brief 시작한다.
**********************************************************************************************************************/
ExBool ClientService::Start()
{
    if ( false == CanStart() )
        return false;

    const ExInt32 sessionCount = GetMaxSessionCount();
    for ( ExInt32 i = 0; i < sessionCount; i++ )
    {
        SessionPtr session = CreateSession();
        if ( false == session->Connect() )
            return false;
    }

    return true;
}

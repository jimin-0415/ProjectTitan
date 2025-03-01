/**********************************************************************************************************************
* @file  ClientService.cpp
*
* @brief ClientService 클래스 cpp 파일
*
* @date  2025.02.28
**********************************************************************************************************************/


#include "pch.h"
#include "ClientService.h"


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
    return true;
}

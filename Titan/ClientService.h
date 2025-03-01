/**********************************************************************************************************************
* @file  ClientService.h
*
* @brief ClientService 클래스 h 파일
*
* @date  2025.02.28
**********************************************************************************************************************/


#pragma once


#include "Service.h"


/**********************************************************************************************************************
* @class ClientService
*
* @brief ClientService 처리 클래스
**********************************************************************************************************************/
class ClientService : public Service
{
public:
    using Super = Service;

public:
    /// 생성자
    ClientService( 
        NetAddress     targetAddress, 
        IocpCorePtr    iocpCore, 
        SessionFactory sessionFactory, 
        ExInt32        maxSessionCount = 1 );

    /// 소멸자
    virtual ~ClientService();

public:
    /// 시작한다.
    virtual ExBool Start() override;
};


/**********************************************************************************************************************
* @file  ServerService.h
*
* @brief ServerService 클래스 h 파일
*
* @date  2025.02.28
**********************************************************************************************************************/


#pragma once


#include "Service.h"


/**********************************************************************************************************************
* @class ServerService
*
* @brief ServerService 처리 클래스
**********************************************************************************************************************/
class ServerService : public Service
{
private:
    using Super = Service;

private:
    /// listener
    ListenerPtr _listener = nullptr;

public:
    /// 생성자
    ServerService( 
        NetAddress     targetAddress,
        IocpCorePtr    iocpCore,
        SessionFactory sessionFactory,
        ExInt32        maxSessionCount = 1 );

    /// 소멸자
    virtual ~ServerService();

public:
    /// 시작한다
    virtual ExBool Start() override;
};


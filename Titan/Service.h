/**********************************************************************************************************************
* @file  Service.h
*
* @brief Service 클래스 h 파일
*
* @date  2025.02.28
**********************************************************************************************************************/


#pragma once


#include "Types.h"
#include "NetAddress.h"
#include "IocpCore.h"
#include "Listener.h"


/**********************************************************************************************************************
* @class Service
*
* @brief Service 각주
**********************************************************************************************************************/
class Service : public enable_shared_from_this< Service >
{
public:
    /// 세션 생성 팩토리
    using SessionFactory = function< SessionPtr( void ) >;

    /// 세션 셋 타입 정의
    using SessionSet = std::set< SessionPtr >;

protected:
    USE_LOCK;

    /// 서비스 타입
    EServiceType _type;

    /// 네트워크 주소
    NetAddress _netAddress = {};

    /// IocpCore 
    IocpCorePtr _iocpCore;

    /// 세션 셋 
    SessionSet _sessions;

    /// 세션 카운트
    ExInt32 _sessionCount = 0;

    /// 최대 세션 카운트
    ExInt32 _maxSessionCount = 0;

    /// 세션 생성 팩토리
    SessionFactory _sessionFactory;

public:
    /// 생성자
    Service( 
        EServiceType   type,
        NetAddress     netAddress,
        IocpCorePtr    iocpCore,
        SessionFactory sessionFactory,
        ExInt32        maxSessionCount = 1 );

    /// 소멸자
    virtual ~Service();

public:
    /// 시작한다.
    virtual ExBool Start() abstract;
    
    /// 서비스를 종료한다.
    virtual ExVoid CloseService();

public:
    /// 세션을 생성한다.
    SessionPtr CreateSession();

    /// 세션을 추가한다.
    ExVoid AddSession( SessionPtr session );

    /// 세션을 해제한다.
    ExVoid ReleaseSession( SessionPtr session );

    /// 시작 여부를 반환한다.
    ExBool CanStart() { return _sessionFactory != nullptr; }

public:
    /// 네트워크 주소를 반환한다.
    const NetAddress& GetNetAddress() { return _netAddress; }

    /// IocpCore를 반환한다.
    const IocpCorePtr& GetIocpCore() { return _iocpCore; }
    
    /// 세션 개수를 반환한다.
    ExInt32 GetSessionCount() { return _sessionCount; }

    /// 최대 세션 개수를 반환한다.
    ExInt32 GetMaxSessionCount() { return _maxSessionCount; }
};

/**********************************************************************************************************************
* @file  ServerService.cpp
*
* @brief ServerService 클래스 cpp 파일
*
* @date  2025.02.28
**********************************************************************************************************************/


#include "pch.h"
#include "ServerService.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
ServerService::ServerService( NetAddress targetAddress, IocpCorePtr iocpCore, SessionFactory sessionFactory, ExInt32 maxSessionCount )
:
Super( EServiceType::Server, targetAddress, iocpCore, sessionFactory, maxSessionCount )
{
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
ServerService::~ServerService()
{
}

/**********************************************************************************************************************
* @brief 시작한다
**********************************************************************************************************************/
ExBool ServerService::Start()
{
	if ( false == CanStart() )
		return false;

	_listener = std::make_shared< Listener >();
	if ( nullptr == _listener )
		return false;

	ServerServicePtr service = static_pointer_cast< ServerService >( shared_from_this() );
	if ( false == _listener->StartAccept( service ) )
		return false;

	return true;
}

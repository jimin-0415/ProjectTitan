/**********************************************************************************************************************
* @file  IocpCore.cpp
*
* @brief IocpCore 클래스 cpp 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"
#include "IocpObject.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
IocpCore::IocpCore()
{
	_iocpHandle = ::CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
	ASSERT_CRASH( _iocpHandle != INVALID_HANDLE_VALUE );
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
IocpCore::~IocpCore()
{
	::CloseHandle( _iocpHandle );
}

/**********************************************************************************************************************
* @brief 등록하다
**********************************************************************************************************************/
ExBool IocpCore::Register( IocpObjectPtr iocpObject )
{
	// 현재는 동시 실행 쓰레드 수에대한 제한 없다.
	return ::CreateIoCompletionPort( iocpObject->GetHandle(), _iocpHandle, 0, 0 );
}

/**********************************************************************************************************************
* @brief 처리하다
**********************************************************************************************************************/
ExBool IocpCore::Dispatch( ExInt32 timeoutMs )
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	if ( ::GetQueuedCompletionStatus(
		_iocpHandle,
		OUT & numOfBytes,
		OUT &key,
		OUT reinterpret_cast<LPOVERLAPPED*>( &iocpEvent ),
		timeoutMs ) )
	{
		IocpObjectPtr iocpObject = iocpEvent->GetOwner();
		iocpObject->Dispatch( iocpEvent, numOfBytes );
	}
	else
	{
		switch ( ExInt32 errorCode = ::WSAGetLastError() )
		{
			case WAIT_TIMEOUT:
			{
				return false;
			} break;
			default:
			{
				IocpObjectPtr iocpObject = iocpEvent->GetOwner();
				iocpObject->Dispatch( iocpEvent, numOfBytes );
			} break;
		}
	}

	return true;
}

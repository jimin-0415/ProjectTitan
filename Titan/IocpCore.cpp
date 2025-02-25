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


// TEMP
IocpCore GIocpCore;


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
ExBool IocpCore::Register( IocpObject* iocpObject )
{
	// 현재는 동시 실행 쓰레드 수에대한 제한 없다.
	return ::CreateIoCompletionPort( iocpObject->GetHandle(), _iocpHandle, reinterpret_cast<ULONG_PTR>( _iocpHandle ), 0 );
}

/**********************************************************************************************************************
* @brief 처리하다
**********************************************************************************************************************/
ExBool IocpCore::Dispatch( ExInt32 timeoutMs )
{
	DWORD numOfBytes = 0;
	IocpObject* iocpObject = nullptr;
	IocpEvent* iocpEvent = nullptr;

	if ( ::GetQueuedCompletionStatus(
		_iocpHandle,
		OUT & numOfBytes,
		OUT reinterpret_cast<PULONG_PTR>( &iocpObject ),
		OUT reinterpret_cast<LPOVERLAPPED*>( &iocpEvent ),
		timeoutMs ) )
	{
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
				iocpObject->Dispatch( iocpEvent, numOfBytes );
			} break;
		}
	}

	return true;
}

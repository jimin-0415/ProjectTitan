/**********************************************************************************************************************
* @file  SocketUtil.h
*
* @brief SocketUtil 클래스 h 파일
*
* @date  2025.02.22
**********************************************************************************************************************/


#pragma once


#include "NetAddress.h"


/**********************************************************************************************************************
* @class SocketUtil
*
* @brief Socket 관련 Util
**********************************************************************************************************************/
class SocketUtil
{
public:
	static LPFN_CONNECTEX    ConnectEx;
	static LPFN_DISCONNECTEX DisconnectEx;
	static LPFN_ACCEPTEX     AcceptEx;

public:
	static void Init();

	static void Clear();

	static SOCKET CreateSocket();

	static ExBool BindWindowsFunction( SOCKET socket, GUID guid, LPVOID* fn );

	static ExBool SetLinger( SOCKET socket, ExUInt32 onOff, ExUInt32 linger );
	static ExBool SetReuseAddress( SOCKET socket, ExBool flag );
	static ExBool SetRecvBufferSize( SOCKET socket, ExInt32 size );
	static ExBool SetSendBufferSize( SOCKET socket, ExInt32 size );
	static ExBool SetTcpNoDelay( SOCKET socket, ExBool flag );
	static ExBool SetUpdateAcceptSocket( SOCKET socket, SOCKET listenSocket );

public:
	static ExBool Bind( SOCKET socket, NetAddress nerAddr );

	static ExBool BindAnyAdress( SOCKET socket, ExUInt16 port );

	static ExBool Listen( SOCKET socket, ExInt32 backlog = SOMAXCONN );

	static ExVoid Close( SOCKET socket );
};

template<typename T >
static inline ExBool SetSockOpt( SOCKET socket, ExInt32 level, ExInt32 optName, T optVal )
{
	return SOCKET_ERROR != ::setsockopt( socket, level, optName, reinterpret_cast<char*>( &optVal ), sizeof( T ) );
}
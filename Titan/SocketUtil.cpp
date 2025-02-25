#include "pch.h"
#include "SocketUtil.h"


LPFN_CONNECTEX    SocketUtil::ConnectEx;
LPFN_DISCONNECTEX SocketUtil::DisconnectEx;
LPFN_ACCEPTEX     SocketUtil::AcceptEx;



void SocketUtil::Init()
{
	// winsock 초기화
	WSADATA wsaData;
	ASSERT_CRASH( ::WSAStartup( MAKEWORD( 2, 2 ), OUT & wsaData ) == 0 );

	// 런타임으로 주소를 어더오는 api
	SOCKET dummySocket = CreateSocket();
	ASSERT_CRASH( BindWindowsFunction( dummySocket, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>( &ConnectEx ) ) );
	ASSERT_CRASH( BindWindowsFunction( dummySocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>( &DisconnectEx ) ) );
	ASSERT_CRASH( BindWindowsFunction( dummySocket, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>( &AcceptEx ) ) );

	Close( dummySocket );
}

void SocketUtil::Clear()
{
	::WSACleanup();
}

SOCKET SocketUtil::CreateSocket()
{
	// WSA_FLAG_OVERLAPPED 비동기 함수 사용.
	return ::WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );
}

ExBool SocketUtil::BindWindowsFunction( SOCKET socket, GUID guid, LPVOID* fn )
{
	// Connect, Disconnect Accept를 불러오기 위한 함수
	DWORD bytes = 0;
	return SOCKET_ERROR != ::WSAIoctl( socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof( guid ), fn, sizeof( *fn ), OUT & bytes, NULL, NULL );
}

ExBool SocketUtil::SetLinger( SOCKET socket, ExUInt32 onOff, ExUInt32 linger )
{
	LINGER option;
	option.l_onoff = onOff;
	option.l_linger = linger;
	
	return SetSockOpt( socket, SOL_SOCKET, SO_LINGER, option );
}

ExBool SocketUtil::SetReuseAddress( SOCKET socket, ExBool flag )
{
	return SetSockOpt( socket, SOL_SOCKET, SO_REUSEADDR, flag );
}

ExBool SocketUtil::SetRecvBufferSize( SOCKET socket, ExInt32 size )
{
	return SetSockOpt( socket, SOL_SOCKET, SO_RCVBUF, size );
}

ExBool SocketUtil::SetSendBufferSize( SOCKET socket, ExInt32 size )
{
	return SetSockOpt( socket, SOL_SOCKET, SO_SNDBUF, size );
}

ExBool SocketUtil::SetTcpNoDelay( SOCKET socket, ExBool flag )
{
	return SetSockOpt( socket, SOL_SOCKET, TCP_NODELAY, flag );
}

ExBool SocketUtil::SetUpdateAcceptSocket( SOCKET socket, SOCKET listenSocket )
{
	return SetSockOpt( socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, listenSocket );
}

ExBool SocketUtil::Bind( SOCKET socket, NetAddress nerAddr )
{
	return SOCKET_ERROR != ::bind( socket, reinterpret_cast<const SOCKADDR*>( &nerAddr.GetSockAddr() ), sizeof( SOCKADDR_IN ) );
}

ExBool SocketUtil::BindAnyAdress( SOCKET socket, ExUInt16 port )
{
	SOCKADDR_IN addressIn;
	addressIn.sin_family = AF_INET;
	addressIn.sin_addr.s_addr = ::htonl( INADDR_ANY );
	addressIn.sin_port = ::htons( port );

	return SOCKET_ERROR != ::bind( socket, reinterpret_cast<const SOCKADDR*>( &addressIn ), sizeof( addressIn ) );
}

ExBool SocketUtil::Listen( SOCKET socket, ExInt32 backlog )
{
	return SOCKET_ERROR != ::listen( socket, backlog ); 
}

ExVoid SocketUtil::Close( SOCKET socket )
{
	if ( socket != INVALID_SOCKET )
		::closesocket( socket );

	socket = INVALID_SOCKET;
}

/**********************************************************************************************************************
* @file  NetAddress.cpp
*
* @brief NetAddress 클래스 cpp 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#include "pch.h"
#include "NetAddress.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
NetAddress::NetAddress( SOCKADDR_IN sockAddr )
:
_sockAddr( sockAddr)
{
}

/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
NetAddress::NetAddress( wstring ip, ExUInt16 port )
{
	::memset( &_sockAddr, 0, sizeof( _sockAddr ) );
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr   = NetUtil::ConvertTo( ip.c_str() );
	_sockAddr.sin_port   = ::htons( port );
}

/**********************************************************************************************************************
* @brief SOCKADDR를 반한한다.
**********************************************************************************************************************/
const SOCKADDR_IN& NetAddress::GetSockAddr() const
{
	return _sockAddr;
}

/**********************************************************************************************************************
* @brief Ip 주소를 반환한다.
**********************************************************************************************************************/
wstring NetAddress::GetIp()
{
	WCHAR buffer[ 100 ];
	::InetNtopW( AF_INET, &_sockAddr.sin_addr, buffer, len32( buffer ) );
	return buffer;
}

/**********************************************************************************************************************
* @brief Port를 반환한다.
**********************************************************************************************************************/
ExUInt16 NetAddress::GetPort()
{
	return ::ntohs( _sockAddr.sin_port );
}

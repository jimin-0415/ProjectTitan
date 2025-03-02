/**********************************************************************************************************************
* @file  NetAddress.h
*
* @brief NetAddress 클래스 h 파일
*
* @date  2025.02.22
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class NetAddress
*
* @brief 네트워크 관련 주소 
**********************************************************************************************************************/
class NetAddress
{
private:
	/// 소켓 주소(IPv4)
	SOCKADDR_IN _sockAddr = {};

public:
	/// 생성자
	NetAddress() = default;

	/// 생성자
	NetAddress( SOCKADDR_IN sockAddr );
	
	/// 생성자
	NetAddress( wstring ip, ExUInt16 port );

public:
	/// SOCKADDR를 반한한다.
	const SOCKADDR_IN& GetSockAddr() const;
	
	/// Ip 주소를 반환한다.
	wstring GetIp();
	
	/// Port를 반환한다.
	ExUInt16 GetPort();
};

/**********************************************************************************************************************
* @file  EIocpEventType.h
*
* @brief EIocpEventType h 파일
*
* @date  2025.02.23
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class EIocpEventType
*
* @brief Iocp Event 유형 이넘
**********************************************************************************************************************/
enum class EIocpEventType : ExInt8
{
    Connect,    //< 연결 요청 
    Disconnect, //< 연결 종료 요청
    Accept,     //< 연결 수락
    PreRecv,    //< 수신 대기( 0byteRecv )
    Recv,       //< 데이터 수신
    Send,       //< 데이터 송신
    Max,        //< 이 열거자의 최대값
};

/**********************************************************************************************************************
* @class EServiceType
*
* @brief 서비스 타입 이넘
**********************************************************************************************************************/
enum class EServiceType : ExInt8
{
    Server,  //< 서버
    Client,  //< 클라이언트
    Max,     //< 이 열거자의 최대값
};

/**********************************************************************************************************************
* @class EProtocol
*
* @brief 프로토콜
**********************************************************************************************************************/
enum class EProtocol : ExUInt32
{
    S_TEST = 1,
};
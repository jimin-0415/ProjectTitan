/**********************************************************************************************************************
* @file  SendBufferManager.h
*
* @brief SendBufferManager 클래스 h 파일
*
* @date  2025.03.03
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class SendBufferManager
*
* @brief SendBufferManager 처리 클래스
**********************************************************************************************************************/
class SendBufferManager
{
private:
    /// 송신 버퍼 청크 벡터 타입 정의
    using SendBufferChunkVector = std::vector< SendBufferChunkPtr >;

private:
    USE_LOCK;

    /// 송신 버퍼 청크 벡터
    SendBufferChunkVector _sendBufferChunkList;

public:
    /// 버퍼를 연다
    SendBufferPtr Open( ExInt32 size );

    /// 버퍼를 추가한다
    ExVoid Push( SendBufferChunkPtr buffer );

    /// 버퍼를 꺼낸다
    SendBufferChunkPtr Pop();

public:
    /// 버퍼를 추가한다(재사용)
    static ExVoid PushGlobal( SendBufferChunk* buffer );
}; 

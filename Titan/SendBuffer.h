/**********************************************************************************************************************
* @file  SendBuffer.h
*
* @brief SendBuffer 클래스 h 파일
*
* @date  2025.03.02
**********************************************************************************************************************/


#pragma once


class SendBufferChunk;


/**********************************************************************************************************************
* @class SendBuffer
*
* @brief SendBuffer 클래스
**********************************************************************************************************************/
class SendBuffer : public enable_shared_from_this< SendBuffer >
{
private:
    /// 버퍼
    BYTE* _buffer = nullptr;

    /// 할당 크기
    ExUInt32 _allocSize = 0;

    /// 쓰기 크기
    ExUInt32 _writeSize = 0;

    /// 송신 버퍼 청크
    SendBufferChunkPtr _owner;

public:
    /// 생성자
    SendBuffer( SendBufferChunkPtr owner, BYTE* buffer, ExUInt32 allocSize );

    /// 소멸자
    ~SendBuffer();

public:
    /// 버퍼를 닫는다
    ExVoid Close( ExUInt32 writeSize );

public:
    /// 버퍼를 반환한다
    BYTE* GetBuffer() { return _buffer; }
    
    /// 할당 크기를 반환한다
    ExUInt32 GetAllcSize() { return _allocSize; }

    /// 쓰기 크기를 반환한다
    ExUInt32 GetWriteSize() { return _writeSize; }
};


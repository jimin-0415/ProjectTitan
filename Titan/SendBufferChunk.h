/**********************************************************************************************************************
* @file  SendBufferChunk.h
*
* @brief SendBufferChunk 클래스 h 파일
*
* @date  2025.03.03
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class SendBufferChunk
*
* @brief SendBufferChunk 클래스
**********************************************************************************************************************/
class SendBufferChunk : public enable_shared_from_this< SendBufferChunk >
{
private:
    /// 청크 크기
    static const ExUInt32 ChunkSize = 6000;

private:
    /// 버퍼
    std::array< BYTE, ChunkSize > _buffer = {};

    /// 오픈 여부
    ExBool _open = false;

    /// 사용된 크기
    ExUInt32 _usedSize = 0;

public:
    /// 생성자
    SendBufferChunk();
    
    /// 소멸자
    ~SendBufferChunk();

public:
    /// 초기상태로 되돌린다
    ExVoid Reset();

    /// 버퍼를 연다
    SendBufferPtr Open( ExUInt32 allocSize );

    /// 버퍼를 닫는다
    ExVoid Close( ExUInt32 writeSize );

public:
    /// 오픈 여부를 반환한다
    ExBool IsOpen() { return _open; }

    /// 버퍼를 반환한다
    BYTE* Buffer() { return &_buffer[ _usedSize ]; }

    /// 남은 버퍼 크기를 반환한다
    ExUInt32 FreeSize() { return static_cast<ExUInt32>( _buffer.size() - _usedSize ); }
};

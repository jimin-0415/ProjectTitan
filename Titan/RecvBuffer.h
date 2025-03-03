/**********************************************************************************************************************
* @file  RecvBuffer.h
*
* @brief RecvBuffer 클래스 h 파일
*
* @date  2025.03.02
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class RecvBuffer
*
* @brief RecvBuffer 처리 클래스
**********************************************************************************************************************/
class RecvBuffer
{
private:
    /// 버퍼
    std::vector< BYTE > _buffer;
    
    /// 버퍼 사이즈
    ExInt32 _bufferSize = 0;

    /// 예약된 총 버퍼 사이즈
    ExInt32 _capacity = 0;
    
    /// 읽기 위치
    ExInt32 _readPos = 0;
    
    /// 쓰기 위치
    ExInt32 _writePos = 0;

private:
    static const ExInt32 s_bufferCount = 10;

public:
    /// 생성자
    RecvBuffer( ExInt32 bufferSize );
    
    /// 소멸자
    ~RecvBuffer();

public:
    /// 버퍼 위치를 옮긴다
    ExVoid ShiftBuffer();

    /// 버퍼를 읽었을 때 처리한다
    ExBool OnRead( ExInt32 numOfBytes );

    /// 버퍼를 쓸때 처리한다
    ExBool OnWrite( ExInt32 numOfBytes );

public:
    /// 읽기 버퍼를 반환한다
    BYTE* GetReadBuffer() { return &_buffer[ _readPos ]; }

    /// 쓰기 버퍼를 반환한다
    BYTE* GetWriteBuffer() { return &_buffer[ _writePos ]; }

    /// 읽을 수 있는 버퍼크기를 반환한다
    ExInt32 DataSize() { return _writePos - _readPos; }

    /// 남은 버퍼 크기를 반환한다
    ExInt32 FreeSize() { return _capacity - _writePos; }
};

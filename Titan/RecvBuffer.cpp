/**********************************************************************************************************************
* @file  RecvBuffer.cpp
*
* @brief RecvBuffer 클래스 cpp 파일
*
* @date  2025.03.02
**********************************************************************************************************************/


#include "pch.h"
#include "RecvBuffer.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
RecvBuffer::RecvBuffer( ExInt32 bufferSize )
:
_bufferSize( bufferSize ),
_capacity  ( bufferSize * s_bufferCount )
{
    _buffer.resize( _capacity );
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
RecvBuffer::~RecvBuffer()
{
    // empty;
}

/**********************************************************************************************************************
* @brief 버퍼 위치를 옮긴다
**********************************************************************************************************************/
ExVoid RecvBuffer::ShiftBuffer()
{
    ExInt32 dataSize = DataSize();
    if ( dataSize == 0 )
    {
        // 읽기,쓰기 커서가 동일 위치라면 둘다 리셋.
        _readPos = _writePos = 0;
    }
    else
    {
        if ( FreeSize() < _bufferSize )
        {
            ::memcpy( &_buffer[ 0 ], &_buffer[ _readPos ], dataSize );
            _readPos = 0;
            _writePos = dataSize;
        }
    }
}

/**********************************************************************************************************************
* @brief 버퍼를 읽었을 때 처리한다
**********************************************************************************************************************/
ExBool RecvBuffer::OnRead( ExInt32 numOfBytes )
{
    if ( numOfBytes > DataSize() )
        return false;

    _readPos += numOfBytes;
    return true;
}

/**********************************************************************************************************************
* @brief 버퍼를 쓸때 처리한다
**********************************************************************************************************************/
ExBool RecvBuffer::OnWrite( ExInt32 numOfBytes )
{
    if ( numOfBytes > FreeSize() )
        return false;
    
    _writePos += numOfBytes;
    return true;
}

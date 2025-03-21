/**********************************************************************************************************************
* @file  BufferWriter.cpp
*
* @brief BufferWriter 클래스 cpp 파일
*
* @date  2025.03.08
**********************************************************************************************************************/


#include "pch.h"
#include "BufferWriter.h"


/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
BufferWriter::BufferWriter()
{
}

/**********************************************************************************************************************
* @brief 생성자
**********************************************************************************************************************/
BufferWriter::BufferWriter( BYTE* buffer, ExInt32 size, ExUInt32 pos )
:
_buffer( buffer),
_size  ( size  ),
_pos   ( pos   )
{
}

/**********************************************************************************************************************
* @brief 소멸자
**********************************************************************************************************************/
BufferWriter::~BufferWriter()
{
}

/**********************************************************************************************************************
* @brief 데이터를 읽는다
**********************************************************************************************************************/
ExBool BufferWriter::Write( ExVoid* src, ExUInt32 len )
{
    if ( FreeSize() < len )
        return false;

    ::memcpy( &_buffer[ _pos ], src, len );
    _pos += len;

    return true;
}

/**********************************************************************************************************************
* @file  BufferWriter.h
*
* @brief BufferWriter 클래스 h 파일
*
* @date  2025.03.08
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class BufferWriter
*
* @brief BufferWriter 처리 클래스
**********************************************************************************************************************/
class BufferWriter
{
private:
	/// 버퍼
	BYTE* _buffer = nullptr;

	/// 크기
	ExUInt32 _size = 0;

	/// 위치
	ExUInt32 _pos = 0;

public:
	/// 생성자
	BufferWriter();

	/// 생성자
	BufferWriter( BYTE* buffer, ExInt32 size, ExUInt32 pos = 0 );

	/// 소멸자
	~BufferWriter();

public:
	/// 데이터를 읽는다
	ExBool Write( ExVoid* src, ExUInt32 len );

public:
	/// 버퍼를 반환한다
	BYTE* Buffer() { return _buffer; }

	/// 크기를 반환한다
	ExUInt32 Size() { return _size; }

	/// 읽기 버퍼 크기를 반환한다
	ExUInt32 WriteSize() { return _pos; }

	/// 남은 버퍼 크기를 반환한다
	ExUInt32 FreeSize() { return _size - _pos; }

public:
	/// 데이터를 읽는다
	template< typename T >
	ExBool Write( T* src ) { return Write( src, sizeof( T ) ); }

	/// 예약한다
	template< typename T >
	T* Reserve();

	/// 연산자 오버로딩
	template< typename T >
	BufferWriter& operator<<( const T& src );

	/// 연산자 오버로딩
	template< typename T >
	BufferWriter& operator<<( T&& src );
};

/**********************************************************************************************************************
* @brief 예약한다
**********************************************************************************************************************/
template< typename T >
inline T* BufferWriter::Reserve()
{
	if ( FreeSize() < sizeof( T ) )
		return nullptr;

	T* ret = reinterpret_cast<T*>( &_buffer[ _pos ] );
	_pos += sizeof( T );

	return ret;
}

/**********************************************************************************************************************
* @brief 연산자 오버로딩
**********************************************************************************************************************/
template< typename T >
inline BufferWriter& BufferWriter::operator<<( const T& src )
{
	*reinterpret_cast<T*>( &_buffer[ _pos ] ) = src;
	_pos += sizeof( T );
	return *this;
}

/**********************************************************************************************************************
* @brief 연산자 오버로딩
**********************************************************************************************************************/
template< typename T >
inline BufferWriter& BufferWriter::operator<<( T&& src )
{
	using DataType = std::remove_reference_t< T >;
	*reinterpret_cast< DataType* >( &_buffer[ _pos ] ) = std::forward< DataType >( src );
	_pos += sizeof( T );
	return *this;
}

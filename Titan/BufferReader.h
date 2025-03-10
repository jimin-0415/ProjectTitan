/**********************************************************************************************************************
* @file  BufferReader.h
*
* @brief BufferReader 클래스 h 파일
*
* @date  2025.03.08
**********************************************************************************************************************/


#pragma once


/**********************************************************************************************************************
* @class BufferReader
*
* @brief BufferReader 처리 클래스
**********************************************************************************************************************/
class BufferReader
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
	BufferReader();

	/// 생성자
	BufferReader( BYTE* buffer, ExInt32 size, ExUInt32 pos = 0 );
	
	/// 소멸자
	~BufferReader();

public:
	/// 데이터를 미리본다
	ExBool Peek( ExVoid* dest, ExUInt32 len );
	
	/// 데이터를 읽는다
	ExBool Read( ExVoid* dest, ExUInt32 len );

public:
	/// 버퍼를 반환한다
	BYTE* Buffer() { return _buffer; }
	
	/// 크기를 반환한다
	ExUInt32 Size() { return _size; }
	
	/// 읽기 버퍼 크기를 반환한다
	ExUInt32 ReadSize() { return _pos; }
	
	/// 남은 버퍼 크기를 반환한다
	ExUInt32 FreeSize() { return _size - _pos; }

public:
	/// 데이터를 미리본다
	template<typename T>
	ExBool Peek( T* dest ) { return Peek( dest, sizeof( T ) ); }

	/// 데이터를 읽는다
	template<typename T>
	ExBool Read( T* dest ) { return Read( dest, sizeof( T ) ); }

	/// 연산자 오버로딩
	template<typename T>
	BufferReader& operator>>( OUT T& dest );
};

/**********************************************************************************************************************
* @brief 연산자 오버로딩
**********************************************************************************************************************/
template<typename T>
inline BufferReader& BufferReader::operator>>( OUT T& dest )
{
	dest = *reinterpret_cast<T*>( &_buffer[ _pos ] );
	_pos += sizeof( T );
	return *this;
}

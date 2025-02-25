/**********************************************************************************************************************
* @file  Types.h
*
* @brief 타입 정의 헤더 파일 
*
* @date  2025.02.15
**********************************************************************************************************************/


#pragma once


using ExByte   = unsigned char;
using ExUInt8  = unsigned __int8;
using ExUInt16 = unsigned __int16;
using ExUInt32 = unsigned __int32;
using ExUInt64 = unsigned __int64;
using ExInt8   = __int8;
using ExInt16  = __int16;
using ExInt32  = __int32;
using ExInt64  = __int64;

using ExBool   = bool;
using ExFloat  = float;
using ExDouble = double;
using ExVoid   = void;

using ExMutex = std::mutex;

template<typename T>
using ExAtomic = std::atomic<T>;

template<typename T>
using ExUniqueLock = std::unique_lock<T>;

template<typename T>
using ExLockGuard = std::lock_guard<T>;

template<typename T>
using ExSharedPtr = std::shared_ptr<T>;

#define size16(val) static_cast<ExInt16>( sizeof( val ) )
#define size32(val) static_cast<ExInt32>( sizeof( val ) )
#define len16(arr) static_cast<ExInt16>( sizeof( arr ) / sizeof( arr[ 0 ] ) )
#define len32(arr) static_cast<ExInt32>( sizeof( arr ) / sizeof( arr[ 0 ] ) )

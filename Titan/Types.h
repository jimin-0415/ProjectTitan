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

using ExMutex = std::mutex;

template<typename T>
using ExAtomic = std::atomic<T>;

template<typename T>
using ExUniqueLock = std::unique_lock<T>;

template<typename T>
using ExLockGuard = std::lock_guard<T>;

template<typename T>
using ExSharedPtr = std::shared_ptr<T>;
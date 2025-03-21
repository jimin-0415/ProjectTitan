/**********************************************************************************************************************
* @file  LockType.h
*
* @brief LockType.h 파일
*
* @date  2025.02.16
**********************************************************************************************************************/


#pragma once


enum : ExUInt32
{
	AcquireTimeOutTick = 10000,
	MaxSpinCount       = 5000,
	WriteMask          = 0xFFFF'0000,
	ReadMask           = 0x0000'FFFF,
	EmptyMask          = 0x0000'0000,
};
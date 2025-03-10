/**********************************************************************************************************************
* @file  pch.h
*
* @brief Precompiled Header h 파일
*
* @date  2025.02.15
**********************************************************************************************************************/


#pragma once


#ifdef _DEBUG
#pragma comment( lib, "Titan\\Debug\\Titan.lib")
#pragma comment( lib, "Titan\\Debug\\Protocol.lib")
#pragma comment( lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment( lib, "Titan\\Release\\Titan.lib")
#pragma comment( lib, "Titan\\Release\\Protocol.lib")
#pragma comment( lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "CorePch.h"

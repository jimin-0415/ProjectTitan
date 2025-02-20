/**********************************************************************************************************************
* @file  CorePch.h
* 
* @brief Core Precompiled Header 클래스 h 파일
* 
* @date  2025.02.15
**********************************************************************************************************************/


#pragma once


#include <atomic>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <windows.h>
#include "Types.h"
#include "CoreGlobal.h"
#include "CoreTLS.h"
#include "CoreMacro.h"
#include "Noncopyable.h"
#include "LockType.h"
#include "RWLock.h"
#include "RWSpinLock.h"
#include "ReadLockGuard.h"
#include "WriteLockGuard.h"


using namespace std;


/**********************************************************************************************************************
* @class CorePch
*
* @brief 코어 Precompiled Header 클래스
**********************************************************************************************************************/
class CorePch
{
};

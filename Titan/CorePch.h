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
#include <functional>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "Types.h"
#include "EnumTypes.h"
#include "IocpCore.h"
#include "TObjectBase.h"
#include "CoreGlobal.h"
#include "CoreTLS.h"
#include "CoreMacro.h"
#include "Noncopyable.h"
#include "NetUtil.h"
#include "LockType.h"
#include "RWLock.h"
#include "RWSpinLock.h"
#include "ReadLockGuard.h"
#include "WriteLockGuard.h"


#pragma comment(lib,"ws2_32.lib")


using namespace std;


/**********************************************************************************************************************
* @class CorePch
*
* @brief 코어 Precompiled Header 클래스
**********************************************************************************************************************/
class CorePch
{
};

#pragma once


#ifdef _DEBUG
#pragma comment( lib, "Titan\\Debug\\Titan.lib")
#pragma comment( lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment( lib, "Titan\\Release\\Titan.lib")
#pragma comment( lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

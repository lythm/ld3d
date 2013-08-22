
#pragma warning(disable: 4251)
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifndef _USRDLL

#define _DLL_API									extern"C" __declspec(dllimport)
#define _DLL_CLASS									__declspec(dllimport)
#else

#define _DLL_API									extern"C" __declspec(dllexport)
#define _DLL_CLASS									__declspec(dllexport)
#endif

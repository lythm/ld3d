#pragma once

#if defined(_WIN64) || defined(_WIN32)
#pragma warning(disable: 4251)

#ifdef	_USRDLL
#define EXPORT_CLASS	__declspec(dllexport)
#define EXPORT_API		__declspec(dllexport) 
#define EXPORT_C_API	extern "C" __declspec(dllexport) 
#else
#define EXPORT_CLASS	__declspec(dllimport)
#define EXPORT_API		__declspec(dllimport)
#define EXPORT_C_API	extern "C"
#endif

#endif



#ifdef __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR

#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
#define EXPORT_CLASS
#define EXPORT_API
#define EXPORT_C_API	extern "C"
#else
#error "unknown mac os"
#endif

#endif





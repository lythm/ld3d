#pragma once


typedef unsigned char									uint8;
typedef char											int8;

typedef unsigned short									uint16;
typedef short											int16;

typedef unsigned int									uint32;
typedef int												int32;

#if defined(_WIN64) || defined(_WIN32)
typedef unsigned __int64								uint64;
typedef __int64											int64;
#endif

#ifdef __APPLE__
#include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR

    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC

        typedef long long                                   int64;
        typedef unsigned long long                          uint64;
    #else
        #error "unknown mac os"
    #endif

#endif

#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
	// ios simulator
#elif TARGET_OS_IPHONE
	// iOS device
#elif TARGET_OS_MAC
	// osx
#else
	#error "unknown mac os"
#endif



#include <dlfcn.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <iconv.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <errno.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/wait.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>



#include <mach/mach.h>
#include <mach/mach_time.h>


#define _DLL_API									extern"C"
#define _DLL_CLASS

#define _stricmp                                    strcasecmp
#define stricmp                                     strcasecmp

#pragma once


#include "platform_types.h"


#if defined(_WIN64) || defined(_WIN32)
#include "platform_win.inl"
#endif

#ifdef __APPLE__
#include "platform_apple.inl"
#endif


#ifdef __linux__
#include "platform_linux.inl"
#endif



namespace ld3d
{

	extern"C" uint64						os_get_tick();


	extern"C" void* 						os_load_module(const char* szModule);
	extern"C" void							os_unload_module(void* mod);

	extern"C" void*							os_find_proc(void* mod, const char* szProc);

	extern"C" void							os_sleep(uint32 ms);

	extern"C" void							os_console_write(const wchar_t* szText);

	extern"C" uint64						os_create_process(const char* szFile, const char* argv[]);
	extern"C" void							os_kill_process(uint64 pid);

	extern"C" int32							os_int32_interlocked_add(volatile long* v, long a);


	extern"C" uint64						os_get_pid();

}








#include "platform/platform.h"

#if defined(_WIN32) || defined(_WIN64)

#include <string>


namespace ld3d
{
	uint64 os_get_tick()
	{
		return GetTickCount64();
	}

	void* os_load_module(const char* szModule)
	{
		return LoadLibraryA(szModule);
	}
	void os_unload_module(void* mod)
	{
		FreeLibrary((HMODULE)mod);
	}

	void* os_find_proc(void* mod, const char* szProc)
	{
		return GetProcAddress((HMODULE)mod, szProc);
	}

	void os_sleep(uint32 ms)
	{
		Sleep(ms);
	}

	uint64 os_create_process(const char* szFile, const char* argv[])
	{
		std::string cmdline = ""; 

		for(int i = 0; argv[i]; ++i)
		{
			cmdline += argv[i];
			cmdline += " ";
		}

		std::string filename(szFile);

		//cmdline = filename + " " + cmdline;

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		if(FALSE == CreateProcessA(szFile, (char*)cmdline.c_str(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			return uint64(-1);
		}

		return pi.dwProcessId;
	}

	void os_kill_process(uint64 pid)
	{
		HANDLE processhandle = OpenProcess(1,0,(DWORD)pid);
		if(processhandle !=NULL)
			TerminateProcess(processhandle,0);
	}

	int32 os_int32_interlocked_add(volatile long* v, long a)
	{
		return InterlockedExchangeAdd(v, a);
	}


	uint64 os_get_pid()
	{
		return GetCurrentProcessId();
	}
}

#endif





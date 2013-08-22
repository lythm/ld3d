#include "platform/platform.h"


#ifdef __linux__


namespace ld3d
{

	uint64 os_get_tick()
	{
		/*struct timeval current;
		gettimeofday(&current,NULL);
		return current.tv_sec*1000+ current.tv_usec/1000;*/
		timespec current;
		clock_gettime(CLOCK_MONOTONIC, &current);
		return current.tv_sec*1000 + current.tv_nsec/1000;

	}
	void* os_load_module(const char* szModule)
	{
		void* ret = dlopen(szModule,RTLD_NOW);

		if(ret == NULL)
		{
			printf("# platform::load_module[%s] failed %s\n", szModule, dlerror());
		}
		return ret;
	}
	void os_unload_module(void* mod)
	{
		dlclose(mod);
	}

	void* os_find_proc(void* mod, const char* szProc)
	{
		return dlsym(mod, szProc);
	}

	void os_sleep(uint32 ms)
	{
		usleep( ms * 1000);
	}


	uint64 os_create_process(const char* szFile, const char* argv[])
	{
		uint64 pid = fork();

		if(pid == 0)
		{
			execv(szFile, (char*const*)argv);
		}

		return pid;
	}
	void os_kill_process(uint64 pid)
	{
		kill(pid,9);		
	}

	int32 os_int32_interlocked_add(volatile long* v, long a)
	{
		return __sync_add_and_fetch(v, a);
	}



	uint64 os_get_pid()
	{
		return getpid();
	}
}

#endif

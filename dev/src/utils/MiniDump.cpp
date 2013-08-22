#include "utils_pch.h"
#include "utils/MiniDump.h"

#if 0

#include  "Dbghelp.h"
#include <tchar.h>
#include "strsafe.h"

namespace ld3d
{

	LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(
		LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
	{
		return NULL;
	}

	BOOL PreventSetUnhandledExceptionFilter()
	{
		HMODULE hKernel32 = LoadLibrary("kernel32.dll");
		if (hKernel32 == NULL) return FALSE;
		void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
		if(pOrgEntry  == NULL) return FALSE;
		unsigned char newJump[ 100 ];
		UINT_PTR dwOrgEntryAddr = (UINT_PTR) pOrgEntry;
		dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far
		void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
		UINT_PTR dwNewEntryAddr = (UINT_PTR) pNewFunc;
		UINT_PTR dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;

		newJump[ 0 ] = 0xE9;  // JMP absolute
		memcpy(&newJump[ 1 ], &dwRelativeAddr, sizeof(pNewFunc));
		SIZE_T bytesWritten;
		BOOL bRet = WriteProcessMemory(GetCurrentProcess(),
			pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
		return bRet;
	}


	typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess , 
											DWORD dwPid, 
											HANDLE hFile, 
											MINIDUMP_TYPE DumpType, 
											CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, 
											CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, 
											CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

	LPTOP_LEVEL_EXCEPTION_FILTER				MiniDump::s_PrevFilter			= NULL;
	std::string								MiniDump::m_strFilePrefix		= "";
	MiniDump::MiniDump(void)
	{
	}

	MiniDump::~MiniDump(void)
	{
	}

	void MiniDump::Begin(const std::string& strFilePrefix)
	{
		//SetErrorMode(SEM_FAILCRITICALERRORS) ; 
		s_PrevFilter = SetUnhandledExceptionFilter(UnHandledExceptionFilter) ; 

		BOOL bRet = PreventSetUnhandledExceptionFilter();

		m_strFilePrefix = strFilePrefix;
		return ; 
	}
	void MiniDump::End()
	{
		SetUnhandledExceptionFilter(s_PrevFilter) ; 
	}
	//Unhandled Exception出现的时候，转向的Callback

	LONG WINAPI MiniDump::UnHandledExceptionFilter(struct _EXCEPTION_POINTERS *exceptionInfo) 
	{ 

		HMODULE DllHandle = NULL;
		//Windows 2000之前，必须另外分配DBGHELP
		//这里使用的是包含在DBGHELP.DLL内的函数，一定要加载

		DllHandle = LoadLibrary(_T("./DBGHELP.DLL")) ; 

		if (DllHandle) 
		{ 
			//获得Dump创建文件的过程
			//在DBGHELP.DLL内打开MiniDumpWirteDump，定义为Dump
			//利用它创建Dump文件

			MINIDUMPWRITEDUMP Dump = (MINIDUMPWRITEDUMP) GetProcAddress(DllHandle , "MiniDumpWriteDump") ; 
			if (Dump) 
			{ 
				TCHAR DumpPath[MAX_PATH] = {0,}; 
				SYSTEMTIME SystemTime ; 
				//获取当前时间
				GetLocalTime(&SystemTime) ;
				//以当前时间为基准，创建Load文件
				StringCchPrintf(DumpPath, MAX_PATH, _T("%s %d-%d-%d %d_%d_%d.dmp"), 
					m_strFilePrefix.c_str(),
					SystemTime .wYear , 
					SystemTime .wMonth, 
					SystemTime .wDay, 
					SystemTime .wHour , 
					SystemTime .wMinute , 
					SystemTime .wSecond) ;
				//创建文件

				HANDLE FileHandle = CreateFile( 
					DumpPath, 
					GENERIC_WRITE, 
					FILE_SHARE_WRITE, 
					NULL, CREATE_ALWAYS, 
					FILE_ATTRIBUTE_NORMAL, 
					NULL) ;

				//文件创建成功的时候

				if (FileHandle != INVALID_HANDLE_VALUE) 
				{ 
					_MINIDUMP_EXCEPTION_INFORMATION MiniDumpExceptionInfo; 
					//保存MiniDump异常信息的结构体
					MiniDumpExceptionInfo.ThreadId = GetCurrentThreadId() ; 
					MiniDumpExceptionInfo.ExceptionPointers = exceptionInfo; 
					MiniDumpExceptionInfo.ClientPointers = NULL;
					//运行当前Process的Dump
					//这里的Dump利用的是上面DBGHELP.DLL中打开的文件
					//通过它创建Dump文件
					BOOL Success = Dump( 
						GetCurrentProcess() , 
						GetCurrentProcessId() , 
						FileHandle, //事先生成的文件句柄值
						//MiniDumpNormal , 
						MiniDumpWithFullMemory,
						&MiniDumpExceptionInfo, //异常信息
						NULL, 
						NULL) ; 

					if (Success) 
					{
						//成功的时候

						CloseHandle(FileHandle) ; 
						return EXCEPTION_EXECUTE_HANDLER; 
					} 
				} 
				CloseHandle(FileHandle) ; 
			} 
		} 
		return EXCEPTION_CONTINUE_SEARCH; 
	} 
}

#endif
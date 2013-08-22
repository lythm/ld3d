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
	//Unhandled Exception���ֵ�ʱ��ת���Callback

	LONG WINAPI MiniDump::UnHandledExceptionFilter(struct _EXCEPTION_POINTERS *exceptionInfo) 
	{ 

		HMODULE DllHandle = NULL;
		//Windows 2000֮ǰ�������������DBGHELP
		//����ʹ�õ��ǰ�����DBGHELP.DLL�ڵĺ�����һ��Ҫ����

		DllHandle = LoadLibrary(_T("./DBGHELP.DLL")) ; 

		if (DllHandle) 
		{ 
			//���Dump�����ļ��Ĺ���
			//��DBGHELP.DLL�ڴ�MiniDumpWirteDump������ΪDump
			//����������Dump�ļ�

			MINIDUMPWRITEDUMP Dump = (MINIDUMPWRITEDUMP) GetProcAddress(DllHandle , "MiniDumpWriteDump") ; 
			if (Dump) 
			{ 
				TCHAR DumpPath[MAX_PATH] = {0,}; 
				SYSTEMTIME SystemTime ; 
				//��ȡ��ǰʱ��
				GetLocalTime(&SystemTime) ;
				//�Ե�ǰʱ��Ϊ��׼������Load�ļ�
				StringCchPrintf(DumpPath, MAX_PATH, _T("%s %d-%d-%d %d_%d_%d.dmp"), 
					m_strFilePrefix.c_str(),
					SystemTime .wYear , 
					SystemTime .wMonth, 
					SystemTime .wDay, 
					SystemTime .wHour , 
					SystemTime .wMinute , 
					SystemTime .wSecond) ;
				//�����ļ�

				HANDLE FileHandle = CreateFile( 
					DumpPath, 
					GENERIC_WRITE, 
					FILE_SHARE_WRITE, 
					NULL, CREATE_ALWAYS, 
					FILE_ATTRIBUTE_NORMAL, 
					NULL) ;

				//�ļ������ɹ���ʱ��

				if (FileHandle != INVALID_HANDLE_VALUE) 
				{ 
					_MINIDUMP_EXCEPTION_INFORMATION MiniDumpExceptionInfo; 
					//����MiniDump�쳣��Ϣ�Ľṹ��
					MiniDumpExceptionInfo.ThreadId = GetCurrentThreadId() ; 
					MiniDumpExceptionInfo.ExceptionPointers = exceptionInfo; 
					MiniDumpExceptionInfo.ClientPointers = NULL;
					//���е�ǰProcess��Dump
					//�����Dump���õ�������DBGHELP.DLL�д򿪵��ļ�
					//ͨ��������Dump�ļ�
					BOOL Success = Dump( 
						GetCurrentProcess() , 
						GetCurrentProcessId() , 
						FileHandle, //�������ɵ��ļ����ֵ
						//MiniDumpNormal , 
						MiniDumpWithFullMemory,
						&MiniDumpExceptionInfo, //�쳣��Ϣ
						NULL, 
						NULL) ; 

					if (Success) 
					{
						//�ɹ���ʱ��

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
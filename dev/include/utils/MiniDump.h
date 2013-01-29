#pragma once

#include <string>
#include <Windows.h>

namespace ld3d
{
	class MiniDump
	{
	public:
		MiniDump(void);
		virtual ~MiniDump(void);

		static void										Begin(const std::wstring& strFilePrefix);
		static void										End();
	private:
		static LONG WINAPI								UnHandledExceptionFilter(struct _EXCEPTION_POINTERS *exceptionInfo) ;

		static LPTOP_LEVEL_EXCEPTION_FILTER				s_PrevFilter;
		static std::wstring								m_strFilePrefix;
	};
}
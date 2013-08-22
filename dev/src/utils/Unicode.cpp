#include "utils_pch.h"
#include "utils/Unicode.h"



#include <windows.h>

namespace ld3d
{
	Unicode::Unicode(void)
	{
	}

	Unicode::~Unicode(void)
	{
	}

	bool Unicode::ANSI_2_UTF16(const std::string& ansi, std::wstring& utf16)
	{

		int n = MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, NULL, 0);


		if(n <= 0)
			return false;

		
		if(n >= MAX_CONVERT_COUNT)
			return false;

		
		wchar_t str[MAX_CONVERT_COUNT + 1];

		
		int ret = MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, str, n + 1);

		
		if(ret != n)
		{

			return false;
		}

		utf16 = str;

		return true;
	}

	bool Unicode::UTF16_2_UTF8(const std::wstring& utf16, std::string& utf8)
	{
		int n = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, NULL, 0, 0, 0);
		
		if(n <= 0)
			return false;

		if(n >= MAX_CONVERT_COUNT)
			return false;

		char str[MAX_CONVERT_COUNT + 1];

		int ret = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, str, n + 1, 0, 0);

		if(ret != n)
			return false;

		utf8 = str;
		return true;
	}

	bool Unicode::UTF8_2_UTF16(const std::string& utf8, std::wstring& utf16)
	{

		int n = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);

		if(n <= 0)
			return false;

		if(n >= MAX_CONVERT_COUNT)
			return false;

		wchar_t str[MAX_CONVERT_COUNT + 1];

		int ret = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, str, n + 1);

		if(ret != n)
			return false;

		utf16 = str;
		
		return true;

	}


	bool Unicode::UTF16_2_ANSI(const std::wstring& utf16, std::string& szAnsi)
	{

		int n = WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, NULL, 0, 0, 0);
		
		if(n <= 0)
			return false;

		if(n >= MAX_CONVERT_COUNT)
			return false;

		char str[MAX_CONVERT_COUNT + 1];

		int ret = WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, str, n + 1, 0, 0);

		if(ret != n)
			return false;

		szAnsi = str;
		return true;
	}


}
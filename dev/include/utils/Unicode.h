#pragma once
#include <string>
namespace ld3d
{
	class Unicode
	{
		enum
		{
			MAX_CONVERT_COUNT = 2048,
		};
	public:
		static bool										ANSI_2_UTF16(const std::string& ansi, std::wstring& utf16);
		static bool										UTF8_2_UTF16(const std::string& utf8, std::wstring& utf16);

		static bool										UTF16_2_ANSI(const std::wstring& utf16, std::string& szAnsi);

		static bool										UTF16_2_UTF8(const std::wstring& utf16, std::string& utf8);

	private:
		Unicode(void);
		~Unicode(void);
	};

}
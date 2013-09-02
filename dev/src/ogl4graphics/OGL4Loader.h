#pragma once

#include <unordered_map>
namespace ld3d
{
	class OGL4Loader
	{
	public:
		OGL4Loader(void);
		virtual ~OGL4Loader(void);

		bool										Load();
		void										Unload();

		bool										IsExtSupported(const std::string& ext);
	private:
		bool										load_module();
		bool										load_version();
		bool										load_extension_info();
		bool										load_api();
		bool										load_wgl();

		void*										_load(const char* szName);
	private:
		std::vector<std::string>					m_exts;
		Version										m_ver;

		void*										m_hLib;
	};
}

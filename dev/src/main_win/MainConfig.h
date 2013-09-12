#pragma once

namespace ld3d
{
	class MainConfig
	{
	public:
		MainConfig(void);
		virtual ~MainConfig(void);

		bool													Load(const std::string& file);

		SysSetting												GetSysSetting();
		boost::filesystem::path									GetMod();
		std::vector<boost::filesystem::path> 					GetPackageList();

		uint32													GetFrameRate();
	private:
		bool													LoadSysSetting(pugi::xml_document& doc);
		bool													LoadPackageList(pugi::xml_document& doc);
		bool													LoadMod(pugi::xml_document& doc);
	private:
		SysSetting												m_sysSetting;

		std::vector<boost::filesystem::path>					m_packages;


		boost::filesystem::path									m_mod;

		uint32													m_frameRate;

	};

	typedef std::shared_ptr<MainConfig>							MainConfigPtr;
}

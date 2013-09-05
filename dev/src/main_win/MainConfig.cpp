#include "pch.h"
#include "MainConfig.h"


namespace ld3d
{
	MainConfig::MainConfig(void)
	{
	}


	MainConfig::~MainConfig(void)
	{
	}
	bool MainConfig::Load(const std::string& file)
	{
		using namespace pugi;
		xml_document doc;

		xml_parse_result result = doc.load_file(file.c_str());

		if(result == false)
		{
			return false;
		}

		if(LoadSysSetting(doc) == false)
		{
			return false;
		}

		if(LoadPackageList(doc) == false)
		{
			return false;
		}

		if(LoadMod(doc) == false)
		{
			return false;
		}
		
		return true;
	}
	bool MainConfig::LoadPackageList(pugi::xml_document& doc)
	{
		using namespace pugi;

		xml_node root = doc.document_element();
		if(root == false)
		{
			return false;
		}

		xml_node package_list = root.child("package_list");
		if(package_list == false)
		{
			return false;
		}

		for(auto package : package_list.children("package"))
		{
			m_packages.push_back(package.text().get());
		}

		return true;
	}
	bool MainConfig::LoadMod(pugi::xml_document& doc)
	{
		using namespace pugi;

		xml_node root = doc.document_element();
		if(root == false)
		{
			return false;
		}

		xml_node mod = root.child("mod");
		if(mod == false)
		{
			return false;
		}

		m_mod = mod.text().get();

		return true;
	}
	bool MainConfig::LoadSysSetting(pugi::xml_document& doc)
	{
		using namespace pugi;

		xml_node root = doc.document_element();
		if(root == false)
		{
			return false;
		}

		xml_node sys = root.child("sys");
		if(sys == false)
		{
			return false;
		}


		xml_node graphics = sys.child("sys_graphics");
		if(graphics == false)
		{
			return false;
		}


		xml_attribute w = graphics.attribute("w");
		if(w)
		{
			m_sysSetting.graphics.frameBufferWidth = w.as_int();
		}
		
		xml_attribute h = graphics.attribute("h");
		if(h)
		{
			m_sysSetting.graphics.frameBufferHeight = h.as_int();
		}

		xml_attribute windowed = graphics.attribute("windowed");
		if(windowed)
		{
			m_sysSetting.graphics.windowed = windowed.as_bool();
		}

		m_sysSetting.graphics.sysMod = graphics.text().get();


		xml_node sound = sys.child("sys_sound");
		if(sound == false)
		{
			return false;
		}
		xml_attribute max_channels = sound.attribute("max_channels");
		if(max_channels)
		{
			m_sysSetting.sound.maxChannels = max_channels.as_int();
		}
		m_sysSetting.sound.sysMod = sound.text().get();

		xml_node network = sys.child("sys_network");
		if(network == false)
		{
			return false;
		}

		m_sysSetting.network.sysMod = network.text().get();


		xml_node physics = sys.child("sys_physics");
		if(physics == false)
		{
			return false;
		}

		m_sysSetting.physics.sysMod = physics.text().get();

		return true;
	}
	boost::filesystem::path MainConfig::GetMod()
	{
		return m_mod;
	}
	std::vector<boost::filesystem::path>  MainConfig::GetPackageList()
	{
		return m_packages;
	}
	SysSetting MainConfig::GetSysSetting()
	{
		return m_sysSetting;
	}
}
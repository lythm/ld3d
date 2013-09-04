#include "utils_pch.h"
#include "utils/Config.h"

namespace ld3d
{
	Config::Config(void)
	{
	}


	Config::~Config(void)
	{
	}
	
	const std::vector<Config::app_string>& Config::Settings(const app_string& key)
	{
		return m_settings[key];
	}
	void Config::AddSetting(const app_string& key, const app_string& value)
	{
		m_settings[key].push_back(value);
	}

	void Config::ReplaceSetting(const app_string& key, std::vector<app_string>& list)
	{
		m_settings[key] = list;
	}

	bool Config::Load(const char* cfg)
	{
		FILE* file = fopen(cfg, "r");

		if(file == NULL)
			return false;

		app_char szLine[1024];

		while(NULL != fgets(szLine, 1023, file))
		{
			ParseLine(szLine);
		}

		fclose(file);

		return true;
	}
	void Config::ReplaceWhiteRight(app_char* line, app_char c)
	{
		app_char* ptr = line + strlen(line) - 1;

		while(ptr != line && (*ptr == L' ' || *ptr == L'\t' || *ptr == L'\n' || *ptr == L'\r'))
		{
			*ptr = c;
			--ptr;
		}

	}
	Config::app_char* Config::ReplaceWhiteLeft(app_char* line, app_char c)
	{
		while(*line != 0 && (*line == L' ' || *line == L'\t' || *line == L'\n' || *line == L'\r'))
		{
			*line = c;
			line++;
		}

		return line;
	}
	Config::app_char* Config::FindWhite(app_char* line)
	{
		while(*line != 0 && (*line != L' ' && *line != L'\t' && *line != L'\n' && *line != L'\r') )
		{
			line++;
		}
		return line;
	}
	void Config::ParseLine(app_char* line)
	{
		if(line[0] == 0 || line[0] == L'#')
			return;

		app_char* key = ReplaceWhiteLeft(line, 0);

		app_char* value = FindWhite(key);

		value = ReplaceWhiteLeft(value, 0);

		if(*key == 0)
			return;

		if(*value == 0)
			return;

		ReplaceWhiteRight(value, 0);

		if(*value == 0)
			return;

		m_settings[key].push_back(value);
	}

	const Config::SettingsMap& Config::Settings()
	{
		return m_settings;
	}
	void Config::Clear()
	{
		m_settings.clear();
	}
}
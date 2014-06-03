#pragma once

#include <string>
#include "platform/platform.h"
#include <vector>

namespace ld3d
{
	class CommandLine
	{
	public:
		CommandLine(const char* szCmdLine);
		CommandLine();
		virtual ~CommandLine(void);

		void						Parse(const char* szCmdLine);
		void						Parse(int argc, char* argv[]);

		const std::string&			GetCmdLine() const;
		const std::string&			GetCmd() const;
		uint32						GetParamCount() const;
		const std::string&			GetParam(uint32 Ind) const;
	private:
		std::string					m_CmdLine;
		std::string					m_cmd;
		std::vector<std::string>	m_params;
	};

	inline
	CommandLine::CommandLine(const char* szCmdLine)
	{
		m_CmdLine				= szCmdLine;
		Parse(szCmdLine);
	}
	inline
	CommandLine::CommandLine()
	{
		m_CmdLine = "";
	}
	inline
	CommandLine::~CommandLine(void)
	{
	}
	inline
	void CommandLine::Parse(int argc, char* argv[])
	{
		std::string str;

		for(int i = 0; i < argc; ++i)
		{
			str += argv[i];
			str += " ";
		}

		Parse(str.c_str());
	}
	inline
	void CommandLine::Parse(const char* szCmdLine)
	{
		m_CmdLine = szCmdLine;
		m_cmd = "";
		int nLen = (int)strlen(szCmdLine);
		std::string tmp;

		int i = 0;
		for(i = 0; i < nLen; ++i)
		{
			if(szCmdLine[i] != ' ')
			{
				m_cmd.push_back(szCmdLine[i]);
			}
			else
			{
				break;
			}
		}
		++i;

		tmp.clear();
		while(szCmdLine[i] == ' ') i++;

		bool nQuote = false;
		m_params.clear();

		for(; i < nLen; ++i)
		{
			if(szCmdLine[i] == '"')
			{
				nQuote = !nQuote;
				continue;
			}
			if(nQuote == false)
			{
				if(szCmdLine[i] == ' ')
				{
					m_params.push_back(tmp);
					tmp.clear();
					continue;
				}
			}
			tmp.push_back(szCmdLine[i]);
		}
		if(tmp.length() != 0 && i == nLen)
		{
			m_params.push_back(tmp);
			tmp.clear();
		}
	}
	inline
	const std::string& CommandLine::GetCmd() const
	{
		return m_cmd;
	}
	inline
	uint32 CommandLine::GetParamCount() const
	{
		return (uint32)m_params.size();
	}
	inline
	const std::string& CommandLine::GetParam(uint32 Ind) const
	{
		return m_params[Ind];
	}

	inline
	const std::string& CommandLine::GetCmdLine() const
	{
		return m_CmdLine;
	}

}
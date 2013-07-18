#include "core_pch.h"
#include "..\..\include\core\MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		BaseParser::BaseParser(BaseParser* parent, std::function<void (const std::string&)> logger)
		{
			m_logger = logger;
			m_parent = parent;
		}


		BaseParser::~BaseParser(void)
		{
		}
		void BaseParser::Error(int line, const std::string& msg)
		{
			if(m_logger)
			{
				m_logger("(" + std::to_string(line + 1) + "): " + msg);
			}

		//	m_bNoError = false;
		}
		BaseParser* BaseParser::Parent()
		{
			return m_parent;
		}
		const std::string& BaseParser::Name()
		{
			return m_name;
		}
		bool BaseParser::FindSymbol(const std::string& name, bool curScope)
		{
			if(m_parent == nullptr)
			{
				return false;
			}
			if(curScope)
			{
				for(auto v : m_parent->m_members)
				{
					if(v->Name() == name)
					{
						return true;
					}
				}
			}
			return false;
		}
	}
}

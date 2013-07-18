#include "core_pch.h"
#include "..\..\include\core\MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		BaseParser::BaseParser(void)
		{
		}


		BaseParser::~BaseParser(void)
		{
		}
		void BaseParser::Error(int line, const std::string& msg)
		{

		}
		bool BaseParser::FindSymbol(const std::string& name, bool curScope)
		{
			return true;
		}
	}
}

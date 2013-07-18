#include "core_pch.h"
#include "..\..\include\core\PassParser.h"

namespace ld3d
{
	namespace material_script
	{
		
		PassParser::PassParser(BaseParser* parent, std::function<void (const std::string&)> logger) : BaseParser(parent, logger)
		{
		}


		PassParser::~PassParser(void)
		{
		}
		bool PassParser::Parse(Lexer* lexer)
		{
			return false;
		}

	}
}

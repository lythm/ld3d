#include "core_pch.h"
#include "..\..\include\core\TechniqueParser.h"

namespace ld3d
{
	namespace material_script
	{
		
		TechniqueParser::TechniqueParser(BaseParser* parent, std::function<void (const std::string&)> logger) : BaseParser(parent, logger)
		{
		}


		TechniqueParser::~TechniqueParser(void)
		{
		}
		bool TechniqueParser::Parse(Lexer* lexer)
		{
			return false;
		}
	}
}
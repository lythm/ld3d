#include "core_pch.h"
#include "..\..\include\core\RenderStateParser.h"

namespace ld3d
{
	namespace material_script
	{
		
		RenderStateParser::RenderStateParser(BaseParser* parent, std::function<void (const std::string&)> logger) : BaseParser(parent, logger)
		{
		}


		RenderStateParser::~RenderStateParser(void)
		{
		}
		bool RenderStateParser::Parse(Lexer* lexer)
		{
			return false;
		}
	}
}

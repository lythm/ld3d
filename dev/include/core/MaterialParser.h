#pragma once

#include "core/MaterialBaseParser.h"


namespace ld3d
{
	namespace material_script
	{
		class MaterialParser : public BaseParser
		{
		public:
			MaterialParser(BaseParser* parent, const Logger& logger = Logger());
			virtual ~MaterialParser();

			bool												Parse(Lexer* lexer, const boost::filesystem::path& dir = "./");

			MaterialPtr											CreateObject(Sys_GraphicsPtr pGraphics);
		private:
			bool												ParseIdentifier(Lexer* lexer);
			
			boost::filesystem::path								m_rootDir;

		};
	}
}

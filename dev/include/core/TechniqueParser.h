#pragma once
#include "core/MaterialBaseParser.h"
namespace ld3d
{
	namespace material_script
	{
		class TechniqueParser  : public BaseParser
		{
		public:
			TechniqueParser(BaseParser* parent, const Logger& logger = Logger());
			virtual ~TechniqueParser(void);

			bool												Parse(Lexer* lexer, const boost::filesystem::path& dir = "./");

			MaterialTechPtr										CreateObject(Sys_GraphicsPtr pGraphics);
		private:
			bool												ParsePass(Lexer* lexer);
			boost::filesystem::path								m_rootDir;
		};


	}
}

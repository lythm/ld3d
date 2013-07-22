#pragma once
#include "core/MaterialBaseParser.h"
namespace ld3d
{
	namespace material_script
	{
		class TechniqueParser  : public BaseParser
		{
		public:
			TechniqueParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~TechniqueParser(void);

			bool												Parse(Lexer* lexer, const boost::filesystem::path& dir = "./");

			MaterialTechPtr										CreateObject(Sys_Graphics2Ptr pGraphics);
		private:
			bool												ParsePass(Lexer* lexer);
			boost::filesystem::path								m_rootDir;
		};


	}
}

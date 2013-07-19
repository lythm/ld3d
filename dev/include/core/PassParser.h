#pragma once
#include "core/MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		class PassParser  : public BaseParser
		{
		public:
			PassParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~PassParser(void);

			bool												Parse(Lexer* lexer);
		private:
			bool												ParseFunctionCall(Lexer* lexer);
		};


	}
}
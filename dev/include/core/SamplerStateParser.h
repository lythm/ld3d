#pragma once

#include "core/MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		class SamplerStateParser : public BaseParser
		{
		public:
			SamplerStateParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~SamplerStateParser(void);

			bool												Parse(Lexer* lexer);

		private:
			bool												ParseState(Lexer* lexer);
		};



	}
}
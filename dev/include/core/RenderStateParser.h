#pragma once

#include "core/MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		class RenderStateParser  : public BaseParser
		{
		public:
			RenderStateParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~RenderStateParser(void);

			bool												Parse(Lexer* lexer);

		private:
			bool												SetState(int line, const std::string& name, const std::string& value);
			bool												ParseState(Lexer* lexer);

		};


	}
}
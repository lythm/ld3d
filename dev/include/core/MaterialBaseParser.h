#pragma once

#include "core/MaterialLexer.h"
namespace ld3d
{
	namespace material_script
	{
		class BaseParser
		{
		public:
			BaseParser(void);
			virtual ~BaseParser(void);

			virtual Token										Parse(Lexer* lexer)											= 0;
			virtual bool										Generate()													= 0;
			virtual bool										NoError()													= 0;

			void												Error(int line, const std::string& msg);
			bool												FindSymbol(const std::string& name, bool curScope);
		};
	}
}

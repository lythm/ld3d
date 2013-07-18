#pragma once

#include "core/MaterialLexer.h"
namespace ld3d
{
	namespace material_script
	{
		class EXPORT_CLASS BaseParser
		{
		public:
			BaseParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~BaseParser(void);

			virtual bool										Parse(Lexer* lexer)											= 0;
			//virtual bool										Generate()													= 0;

			void												Error(int line, const std::string& msg);
			bool												FindSymbol(const std::string& name, bool curScope);

			BaseParser*											Parent();
			const std::string&									Name();
		protected:
			std::function<void (const std::string&)>			m_logger;
			BaseParser*											m_parent;
			std::string											m_name;
			std::vector<BaseParserPtr>							m_members;
		};
	}
}

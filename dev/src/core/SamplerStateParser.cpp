#include "core_pch.h"
#include "..\..\include\core\SamplerStateParser.h"

namespace ld3d
{
	namespace material_script
	{
		SamplerStateParser::SamplerStateParser(BaseParser* parent, std::function<void (const std::string&)> logger) : BaseParser(parent, logger)
		{
		}


		SamplerStateParser::~SamplerStateParser(void)
		{
		}
		bool SamplerStateParser::Parse(Lexer* lexer)
		{
			Token token = lexer->NextToken();

			if(token.type != Token::token_id)
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			m_name = token.str;

			if(FindSymbol(m_name, true) == true)
			{
				Error(token.line, "object '" + m_name + "' already defined.");
				return false;
			}

			token = lexer->NextToken();

			if(token.str != "{")
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			token = lexer->NextToken();

			while(true)
			{
				if(ParseState(lexer) == false)
				{
					return false;
				}

				if(lexer->CurToken().str == "}")
				{
					break;
				}
			}

			token = lexer->NextToken();
			if(token.str == ";")
			{
				lexer->SkipToken(token);
			}

			return true;
		}
		bool SamplerStateParser::ParseState(Lexer* lexer)
		{
			std::string  name;
			Token token						= lexer->CurToken();
			if(token.type != Token::token_id)
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			name = token.str;


			token							= lexer->NextToken();
			if(token.str != "=")
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			token							= lexer->NextToken();
			if(token.type != Token::token_id && token.type != Token::token_number)
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			std::string value = token.str;

			token							= lexer->NextToken();
			if(token.str != ";")
			{
				Error(token.line, "missing ';'.");
				return false;
			}
			
			lexer->SkipToken(token);
			
			return true;
		}
	}
}

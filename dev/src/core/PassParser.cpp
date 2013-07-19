#include "core_pch.h"
#include "..\..\include\core\PassParser.h"

namespace ld3d
{
	namespace material_script
	{
		
		PassParser::PassParser(BaseParser* parent, std::function<void (const std::string&)> logger) : BaseParser(parent, logger)
		{
		}


		PassParser::~PassParser(void)
		{
		}
		bool PassParser::Parse(Lexer* lexer)
		{
			Token token = lexer->CurToken();

			if(token.type != Token::token_id)
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			m_name = token.str;

			if(FindSymbol(m_name, true) != nullptr)
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
				if(ParseFunctionCall(lexer) == false)
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
		bool PassParser::ParseFunctionCall(Lexer* lexer)
		{
			std::string  name;
			Token token						= lexer->CurToken();

			if(token.str == "}")
			{
				return true;
			}

			if(token.type != Token::token_id)
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			name = token.str;

			token							= lexer->NextToken();

			if(token.str != "(")
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			token							= lexer->NextToken();




			std::vector<std::string> params;

			
			while(true)
			{
				if(token.type != Token::token_id && token.type != Token::token_number && token.type != Token::token_string && token.str != ")")
				{
					Error(token.line, "unexpected token: '" + token.str + "'");
					return false;
				}

				if(token.str == ")")
				{
					token = lexer->NextToken();
					break;
				}

				if(token.type == Token::token_id || token.type == Token::token_number || token.type == Token::token_string)
				{
					params.push_back(token.str);
					token = lexer->NextToken();
				}

				if(token.str != "," && token.str != ")")
				{
					Error(token.line, "unexpected token: '" + token.str + "'");
					return false;
				}

				if(token.str == ",")
				{
					token = lexer->NextToken();
				}
			}

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

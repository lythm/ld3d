#include "core_pch.h"
#include "..\..\include\core\MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		BaseParser::BaseParser(BaseParser* parent, std::function<void (const std::string&)> logger)
		{
			m_logger = logger;
			m_parent = parent;
		}


		BaseParser::~BaseParser(void)
		{
		}
		void BaseParser::Error(int line, const std::string& msg)
		{
			if(m_logger)
			{
				m_logger("(" + std::to_string(line + 1) + "): " + msg);
			}
		}
		BaseParser* BaseParser::Parent()
		{
			return m_parent;
		}
		const std::string& BaseParser::Name()
		{
			return m_name;
		}
		BaseParserPtr BaseParser::FindSymbol(const std::string& name, bool curScope)
		{
			if(m_parent == nullptr)
			{
				return BaseParserPtr();
			}
			if(curScope)
			{
				for(auto v : m_parent->m_members)
				{
					if(v->Name() == name)
					{
						return v;
					}
				}
				return false;
			}

			BaseParser* pNode = m_parent;

			while(pNode)
			{
				for(auto v : pNode->m_members)
				{
					if(v->Name() == name)
					{
						return v;
					}
				}
				pNode = pNode->Parent();
			}

			return false;
		}
		bool BaseParser::str_i_cmp(const std::string& s1, const std::string& s2)
		{
			return _stricmp(s1.c_str(), s2.c_str()) == 0;
		}
		bool BaseParser::ParseEnum(const std::string& value, uint32& e, std::pair<std::string, uint32> list[])
		{
			for(int i = 0; list[i] != std::pair<std::string, uint32>(); ++i)
			{
				if(str_i_cmp(value, list[i].first))
				{
					e = list[i].second;
					return true;
				}
			}

			return false;
		}
		bool BaseParser::ValidateEnumValue(const std::string& value, char* list[])
		{
			for(int i = 0; list[i] != 0; ++i)
			{
				if(str_i_cmp(value, list[i]))
				{
					return true;
				}
			}

			return false;
		}
		bool BaseParser::IsNumber(const std::string& value)
		{
			int dot = 0;
			for(auto v : value)
			{
				if(isdigit(v) == 0 && v != '.')
				{
					return false;
				}

				if(v == '.')
				{
					++dot;
				}
			}

			if(dot > 1)
			{
				return false;
			}

			return true;
		}

		bool BaseParser::IsInt(const std::string& value)
		{
			for(auto v : value)
			{
				if(isdigit(v) == 0)
				{
					return false;
				}
			}

			return true;
		}
		bool BaseParser::IsVec4(const std::string& value)
		{
			Lexer lexer(value);

			Token token = lexer.NextToken();
			if(token.str != "{")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.str != ",")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.str != ",")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.str != ",")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.str != "}")
			{
				return false;
			}

			return true;
		}
		bool BaseParser::ParseVec4(const std::string& str, math::Vector4& value)
		{
			Lexer lexer(str);

			Token token = lexer.NextToken();
			if(token.str != "{")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}

			value.x = (Real)token.num;

			token = lexer.NextToken();
			if(token.str != ",")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}
			value.y = (Real)token.num;

			token = lexer.NextToken();
			if(token.str != ",")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}
			value.z = (Real)token.num;

			token = lexer.NextToken();
			if(token.str != ",")
			{
				return false;
			}

			token = lexer.NextToken();
			if(token.type != Token::token_number)
			{
				return false;
			}
			value.w = (Real)token.num;

			token = lexer.NextToken();
			if(token.str != "}")
			{
				return false;
			}

			return true;
		}
		bool BaseParser::ParseVec4(Lexer* lexer, std::string& value)
		{
			Token token = lexer->CurToken();

			value = "";

			if(token.str != "{")
			{
				return false;
			}
			value += "{";

			token = lexer->NextToken();

			// v1
			if(token.type != Token::token_number)
			{
				return false;
			}
			value += token.str;

			token = lexer->NextToken();
			if(token.str != ",")
			{
				return false;
			}

			value += token.str;

			token = lexer->NextToken();
			// v2
			if(token.type != Token::token_number)
			{
				return false;
			}
			value += token.str;

			token = lexer->NextToken();

			if(token.str != ",")
			{
				return false;
			}

			value += token.str;

			token = lexer->NextToken();

			// v3
			if(token.type != Token::token_number)
			{
				return false;
			}
			value += token.str;

			token = lexer->NextToken();

			if(token.str != ",")
			{
				return false;
			}

			value += token.str;

			token = lexer->NextToken();

			// v4
			if(token.type != Token::token_number)
			{
				return false;
			}
			value += token.str;

			token = lexer->NextToken();

			if(token.str != "}")
			{
				return false;
			}

			value += "}";

			token = lexer->NextToken();
			return true;
		}
		bool BaseParser::ParseBool(const std::string& value, bool& ret)
		{
			if(str_i_cmp(value, "true"))
			{
				ret = true;
				return true;
			}
			if(str_i_cmp(value, "false"))
			{
				ret = false;
				return true;
			}

			return false;
		}
		bool BaseParser::ParseNumber(const std::string& value, double& ret)
		{
			if(IsNumber(value) == false)
			{
				return false;
			}

			ret = strtod(value.c_str(), nullptr);
			return true;
		}
		bool BaseParser::ParseFloat(const std::string& value, float& ret)
		{
			double d = -1;
			if(ParseNumber(value, d))
			{
				ret = (float)d;
				return true;
			}

			return false;
		}
		bool BaseParser::ParseInt(const std::string& value, int& ret)
		{
			if(IsInt(value) == false)
			{
				return false;
			}
			ret = strtol(value.c_str(), nullptr, 10);
			return true;
		}
	}
}

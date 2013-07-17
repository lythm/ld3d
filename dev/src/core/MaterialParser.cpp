#include "core_pch.h"
#include "..\..\include\core\MaterialParser.h"
#include "core_utils.h"

namespace ld3d
{
	namespace material_script
	{
		Parser::Parser(void)
		{
			_reset("");
		}

		Parser::~Parser(void)
		{

		}
		bool Parser::Parse(const std::string& src)
		{
			_reset(src);

			ObjectMetaData root;
			root.type = "";
			root.value = "";
			root.parent = nullptr;

			Token token = m_lexer.NextToken();

			while(true)
			{
				switch(token.type)
				{
				case Token::token_misc:
					token = _parse_misc();
					break;

				case Token::token_id:
					token = _parse_identifier(root);
					break;
				case Token::token_eof:
					return true;
				default:
					_log(token.line, "unexpected token: '" + token.str + "'");
					token = m_lexer.NextToken();
					break;
				}
			}

			return true;
		}
		void Parser::_reset(const std::string& src)
		{
			m_lexer.Reset(src);
		}
		void Parser::_log(int line, const std::string& msg)
		{
			log("[" + std::to_string(line + 1) + "]: " + msg);
		}
		Token Parser::_parse_identifier(ObjectMetaData& obj)
		{
			Token token = m_lexer.CurToken();
			Token next_token				= m_lexer.NextToken();

			if(next_token.type == Token::token_id)
			{
				ObjectMetaData child;
				child.type = token.str;
				child.value = next_token.str;
				child.parent = &obj;

				if(_already_defined(child.value, obj))
				{
					_log_already_defined(next_token.line, child);
					return m_lexer.NextToken();;
				}

				next_token = _parse_object(child);

				obj.members.push_back(child);
				return next_token;
			}
			if(next_token.type == Token::token_misc)
			{
				if(next_token.str == "(")
				{
					ObjectMetaData child;
					child.type = "__function_call__";
					child.value = token.str;
					child.parent = &obj;
					next_token = _parse_function_call(child);
					obj.members.push_back(child);
					return next_token;
				}
				if(next_token.str == "=")
				{
					ObjectMetaData child;
					child.type = "__assign__";
					child.value = token.str;
					child.parent = &obj;

					if(_already_defined(child.value, obj))
					{
						
						_log_already_defined(next_token.line, child);
						return m_lexer.NextToken();;
					}

					next_token = _parse_expr_assign(child);
					obj.members.push_back(child);
					return next_token;
				}
			}

			if(token.type == Token::token_eof)
			{
				_log(token.line, "unexpected end of file.");
				return token;
			}

			_log(next_token.line, "unexpected token: '" + next_token.str + "'");
			return next_token;
		}
		Token Parser::_parse_misc()
		{
			Token token = m_lexer.CurToken();

			if(token.str == ";")
			{
				while(token.str == ";")
				{
					token = m_lexer.NextToken();
				}
				return token;
			}

			_log(token.line, "unexpected token: '" + token.str + "'");
			
			return m_lexer.NextToken();
		}

		Token Parser::_parse_object(ObjectMetaData& obj)
		{
			Token token = m_lexer.NextToken();
			
			if(token.str == "{")
			{
				token = m_lexer.NextToken();
				while(true)
				{
					if(token.type == Token::token_id)
					{
						token = _parse_identifier(obj);
						continue;
					}
					if(token.str == "}")
					{
						token = m_lexer.NextToken();

						if(token.str == ";")
						{
							while(token.str == ";")
							{
								token = m_lexer.NextToken();
							}
							return token;
						}
						return token;
					}
					
					break;
				}
			}
			
			if(token.type == Token::token_eof)
			{
				_log(token.line, "unexpected end of file.");
				return token;
			}
			_log(token.line, "unexpected token: '" + token.str + "'");
			return token;
		}
		Token Parser::_parse_function_call(ObjectMetaData& obj)
		{
			Token token = m_lexer.NextToken();

			while(true)
			{
				if(token.type != Token::token_id && token.type != Token::token_number && token.type != Token::token_string && token.str != ")")
				{
					break;
				}

				if(token.str == ")")
				{
					token = m_lexer.NextToken();

					while(token.str == ";")
					{
						token = m_lexer.NextToken();
					}

					return token;
				}
				
				ObjectMetaData param;

				if(token.type == Token::token_id)
				{
					param.type = "__object__";
				}
				if(token.type == Token::token_number)
				{
					param.type = "__number__";
					
				}
				if(token.type == Token::token_string)
				{
					param.type = "__string__";
					
				}
				param.value = token.str;
				param.parent = &obj;
					
				obj.members.push_back(param);


				token = m_lexer.NextToken();
				if(token.str != "," && token.str != ")")
				{
					break;
				}

				if(token.str == ",")
				{
					token = m_lexer.NextToken();
				}
			}

			_log(token.line, "unexpected token: '" + token.str + "'");
			return token;
		}
		Token Parser::_parse_expr_assign(ObjectMetaData& obj)
		{
			Token token = m_lexer.NextToken();
			
			if(token.type == Token::token_number)
			{
				ObjectMetaData value;
				value.type = "__number__";
				value.value = token.str;
				value.parent = &obj;

				obj.members.push_back(value);

				token = m_lexer.NextToken();
			}
			if(token.str == ";")
			{
				while(token.str == ";")
				{
					token = m_lexer.NextToken();
				}
				return token;
			}
			
			if(token.type == Token::token_eof)
			{
				_log(token.line, "unexpected end of file.");
				return token;
			}

			_log(token.line, "';' expected.");
			return token;
		}
		bool Parser::_already_defined(const std::string& value, const ObjectMetaData& scope)
		{
			for(const auto & v : scope.members)
			{
				if(_stricmp(v.value.c_str(), value.c_str()) == 0)
				{
					return true;
				}
			}

			return false;
		}
		void Parser::_log_already_defined(int line, const ObjectMetaData& obj)
		{
			std::string log = obj.value;

			const ObjectMetaData* node = obj.parent;
			while(node)
			{
				if(node->parent != nullptr)
				{
					log = node->value + "." + log;
				}

				node = node->parent;
			}

			_log(line, "object '" + log + "' already defined.");
		}
	}
}

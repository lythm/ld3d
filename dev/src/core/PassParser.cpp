#include "core_pch.h"
#include "..\..\include\core\PassParser.h"
#include "core/MaterialPass.h"
#include "core/Sys_Graphics.h"

namespace ld3d
{
	namespace material_script
	{
		static char* StateList[] = 
		{
			"SetVertexShader", "SetGeometryShader", "SetPixelShader", "SetRenderState", "BindSampler",
		};

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
			std::vector<Token> func;

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

			func.push_back(token);
			
			token							= lexer->NextToken();

			if(token.str != "(")
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			token							= lexer->NextToken();

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
					func.push_back(token);
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

			if(false == SetState(func))
			{
				return false;
			}

			if(token.str != ";")
			{
				Error(token.line, "missing ';'.");
				return false;
			}
			
			lexer->SkipToken(token);
			
			return true;
		}
		bool PassParser::SetState(const std::vector<Token>& func)
		{
			if(ValidateEnumValue(func[0].str, StateList) == false)
			{
				Error(func[0].line, "undefined function call: '" + func[0].str + "'");
				return false;
			}
			//"SetVertexShader"
			
			if(str_i_cmp(func[0].str, "SetVertexShader"))
			{
				if(func.size() != 2)
				{
					Error(func[0].line, "SetVertexShader: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_string)
				{
					Error(func[0].line, "SetVertexShader: arg 0: invalid type, should be string.");
					return false;
				}

				_VertexShader = func[1].str;
				return true;
			}
			//"SetGeometryShader"
			if(str_i_cmp(func[0].str, "SetGeometryShader"))
			{
				if(func.size() != 2)
				{
					Error(func[0].line, "SetGeometryShader: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_string)
				{
					Error(func[0].line, "SetGeometryShader: arg 0: invalid type, should be string.");
					return false;
				}

				_GeometryShader = func[1].str;
				return true;
			}

				
			//"SetPixelShader",
			if(str_i_cmp(func[0].str, "SetPixelShader"))
			{
				if(func.size() != 2)
				{
					Error(func[0].line, "SetPixelShader: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_string)
				{
					Error(func[0].line, "SetPixelShader: arg 0: invalid type, should be string.");
					return false;
				}

				_PixelShader = func[1].str;
				return true;
			}
			//"SetRenderState"
			if(str_i_cmp(func[0].str, "SetRenderState"))
			{
				if(func.size() != 2)
				{
					Error(func[0].line, "SetRenderState: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_id)
				{
					Error(func[0].line, "SetRenderState: arg 0: invalid type, should be renderstate object.");
					return false;
				}

				if(nullptr == FindSymbol(func[1].str, false))
				{
					Error(func[0].line, "SetRenderState: arg 0: undefined symbol: '" + func[1].str + "'");
					return false;
				}

				_RenderState = func[1].str;
				return true;
			}
			//"BindSampler"
			if(str_i_cmp(func[0].str, "BindSampler"))
			{
				if(func.size() != 3)
				{
					Error(func[0].line, "BindSampler: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_string)
				{
					Error(func[0].line, "BindSampler: arg 0: invalid type, should be string.");
					return false;
				}
				if(func[2].type != Token::token_id)
				{
					Error(func[0].line, "BindSampler: arg 1: invalid type, should be sampler object.");
					return false;
				}
				if(nullptr == FindSymbol(func[2].str, false))
				{
					Error(func[0].line, "BindSampler: arg 1: undefined symbol: '" + func[2].str + "'");
					return false;
				}

				_SamplerLink.push_back(SamplerLink(func[1].str, func[2].str));
				_VertexShader = func[1].str;
				return true;
			}
			
			return false;
		}
		MaterialPassPtr	PassParser::CreateObject(Sys_Graphics2Ptr pGraphics)
		{
			return MaterialPassPtr();
		}
	}
}

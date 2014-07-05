#include "core_pch.h"
#include "core/PassParser.h"
#include "core/MaterialPass.h"
#include "core/Sys_Graphics.h"
#include "core/SamplerStateParser.h"
#include "core/RenderStateParser.h"
namespace ld3d
{
	namespace material_script
	{
		static char* StateList[] = 
		{
			"SetVertexShader", "SetGeometryShader", "SetPixelShader", "SetRenderState", "BindSampler",
		};

		PassParser::PassParser(BaseParser* parent, const Logger& logger) : BaseParser(parent, logger)
		{
		}


		PassParser::~PassParser(void)
		{
		}
		bool PassParser::Parse(Lexer* lexer, const boost::filesystem::path& dir)
		{
			m_rootDir = dir;

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
				if(func.size() != 2 && func.size() != 3)
				{
					Error(func[0].line, "SetVertexShader: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_string)
				{
					Error(func[0].line, "SetVertexShader: arg 0: invalid type, should be string.");
					return false;
				}

				if(func[1].str == "")
				{
					_VertexShader = "";
					return true;
				}

				_VertexShader = m_rootDir / func[1].str;

				_VertexShaderEntry = "";
				if(func.size() == 3)
				{
					_VertexShaderEntry = func[2].str;
				}

				if(false == boost::filesystem::exists(_VertexShader))
				{
					Error(func[0].line, "SetVertexShader: file not found: '" + _VertexShader.string() + "'");
					return false;
				}

				return true;
			}
			//"SetGeometryShader"
			if(str_i_cmp(func[0].str, "SetGeometryShader"))
			{
				if(func.size() != 2 && func.size() != 3)
				{
					Error(func[0].line, "SetGeometryShader: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_string)
				{
					Error(func[0].line, "SetGeometryShader: arg 0: invalid type, should be string.");
					return false;
				}

				if(func[1].str == "")
				{
					_GeometryShader = "";
					return true;
				}

				_GeometryShader = m_rootDir / func[1].str;

				_GeometryShaderEntry = "";
				if(func.size() == 3)
				{
					_GeometryShaderEntry = func[2].str;
				}

				if(false == boost::filesystem::exists(_GeometryShader))
				{
					Error(func[0].line, "SetGeometryShader: file not found: '" + _GeometryShader.string() + "'");
					return false;
				}

				
				return true;
			}

				
			//"SetPixelShader",
			if(str_i_cmp(func[0].str, "SetPixelShader"))
			{
				if(func.size() != 2 && func.size() != 3)
				{
					Error(func[0].line, "SetPixelShader: invalid argment count");
					return false;
				}

				if(func[1].type != Token::token_string)
				{
					Error(func[0].line, "SetPixelShader: arg 0: invalid type, should be string.");
					return false;
				}

				if(func[1].str == "")
				{
					_PixelShader = "";
					return true;
				}

				_PixelShader = m_rootDir / func[1].str;

				_PixelShaderEntry = "";
				if(func.size() == 3)
				{
					_PixelShaderEntry = func[2].str;
				}

				if(false == boost::filesystem::exists(_PixelShader))
				{
					Error(func[0].line, "SetPixelShader: file not found: '" + _PixelShader.string() + "'");
					return false;
				}
				
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
				return true;
			}
			
			return false;
		}
		MaterialPassPtr	PassParser::CreateObject(Sys_GraphicsPtr pGraphics)
		{
			ShaderProgramPtr pProgram = pGraphics->CreateShaderProgram();

			if(_VertexShader != "" && pProgram->AttachShaderFromFile(ST_VERTEX_SHADER, _VertexShader.string().c_str(), _VertexShaderEntry) == false)
			{
				Error(0, "failed to create vertex shader: '" + _VertexShader.string() + "'");
				pProgram->Release();
				return nullptr;
			}

			if(_PixelShader != "" && pProgram->AttachShaderFromFile(ST_PIXEL_SHADER, _PixelShader.string().c_str(), _PixelShaderEntry) == false)
			{
				Error(0, "Failed to create pixel shader: '" + _PixelShader.string() + "'");
				pProgram->Release();
				return nullptr;
			}

			if(_GeometryShader != "" && pProgram->AttachShaderFromFile(ST_GEOMETRY_SHADER, _GeometryShader.string().c_str(), _GeometryShaderEntry) == false)
			{
				Error(0, "Failed to create geometry shader: '" + _GeometryShader.string() + "'");
				pProgram->Release();
				return nullptr;
			}

			if(false == pProgram->Link())
			{
				pProgram->Release();
				return nullptr;
			}

			MaterialPassPtr pPass = std::make_shared<MaterialPass>(m_name, pGraphics);
			pPass->AttachProgram(pProgram);

			for(auto v : _SamplerLink)
			{
				SamplerStateParserPtr pParser = std::dynamic_pointer_cast<SamplerStateParser>(FindSymbol(v.second, false));
				if(pParser == nullptr)
				{
					assert(0);
					continue;
				}
				
				if(pProgram->FindParameterByName(v.first.c_str()) == -1)
				{
					Error(0, "sampler name not found: '" + v.first + "'");
					continue;
				}

				pPass->AddSamplerLink(v.first, pParser->CreateObject(pGraphics));
			}
			
			RenderStateParserPtr pRSParser = std::dynamic_pointer_cast<RenderStateParser>(FindSymbol(_RenderState, false));
			if(pRSParser)
			{
				pPass->AttachRenderState(pRSParser->CreateObject(pGraphics));
			}
			else
			{
				pPass->AttachRenderState(pGraphics->CreateRenderState());
			}

			return pPass;
		}
	}
}


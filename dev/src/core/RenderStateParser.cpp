#include "core_pch.h"
#include "..\..\include\core\RenderStateParser.h"

namespace ld3d
{
	namespace material_script
	{
		static char* StateList[] = 
		{
			"BlendFactor", "BlendEnable", "BlendAlphaOP", "BlendRGBOP", "BlendSrcRGB", "BlendDstRGB", "BlendSrcAlpha", "BlendDstAlpha",
			"ColorWrite", "FillMode", "CullMode", "FrontFaceCounterClockWise", "DepthBias", "DepthBiasClamp", "SlopScaledDepthBias",
			"DepthClipEnable", "DepthEnable", "DepthWriteMask", "DepthFunc",  
			"StencilEnable", "FrontFaceStencilFailOP", "FrontFaceStencilDepthFailOP", "FrontFaceStencilPassOP", "FrontFaceStencilFunc",
			"BackFaceStencilFailOP", "BackFaceStencilDepthFailOP", "BackFaceStencilPassOP", "BackFaceStencilFunc",
		};

		static std::pair<std::string, uint32> BlendEnum[] = 
		{
			std::pair<std::string, uint32>("ZERO",						RS_BLEND_ZERO),
			std::pair<std::string, uint32>("ONE",						RS_BLEND_ONE),
			std::pair<std::string, uint32>("SRC_COLOR",					RS_BLEND_SRC_COLOR),
			std::pair<std::string, uint32>("INV_SRC_COLOR",				RS_BLEND_INV_SRC_COLOR),

			std::pair<std::string, uint32>("SRC_ALPHA",					RS_BLEND_SRC_ALPHA),
			std::pair<std::string, uint32>("INV_SRC_ALPHA",				RS_BLEND_INV_SRC_ALPHA),
			std::pair<std::string, uint32>("DEST_ALPHA",				RS_BLEND_DEST_ALPHA),
			std::pair<std::string, uint32>("INV_DEST_ALPHA",			RS_BLEND_INV_DEST_ALPHA),

			std::pair<std::string, uint32>("DEST_COLOR",				RS_BLEND_DEST_COLOR),
			std::pair<std::string, uint32>("INV_DEST_COLOR",			RS_BLEND_INV_DEST_COLOR),
			std::pair<std::string, uint32>("SRC_ALPHA_SAT",				RS_BLEND_SRC_ALPHA_SAT),
			std::pair<std::string, uint32>("BLEND_FACTOR",				RS_BLEND_BLEND_FACTOR),

			std::pair<std::string, uint32>("INV_BLEND_FACTOR",			RS_BLEND_INV_BLEND_FACTOR),
			std::pair<std::string, uint32>("SRC1_COLOR",				RS_BLEND_SRC1_COLOR),
			std::pair<std::string, uint32>("INV_SRC1_COLOR",			RS_BLEND_INV_SRC1_COLOR),
			std::pair<std::string, uint32>("SRC1_ALPHA",				RS_BLEND_SRC1_ALPHA),
			std::pair<std::string, uint32>("INV_SRC1_ALPHA",			RS_BLEND_INV_SRC1_ALPHA),

		};
		static std::pair<std::string, uint32> BlendOPEnum[] = 
		{
			std::pair<std::string, uint32>("ADD",						RS_BLEND_OP_ADD),
			std::pair<std::string, uint32>("SUBTRACT",					RS_BLEND_OP_SUBTRACT),
			std::pair<std::string, uint32>("REV_SUBTRACT",				RS_BLEND_OP_REV_SUBTRACT),
			std::pair<std::string, uint32>("MIN",						RS_BLEND_OP_MIN),

			std::pair<std::string, uint32>("MAX",						RS_BLEND_OP_MAX),

		};

		static std::pair<std::string, uint32> ColorWriteEnum[] = 
		{
			std::pair<std::string, uint32>("RED",						RS_COLOR_WRITE_ENABLE_RED),
			std::pair<std::string, uint32>("GREEN",						RS_COLOR_WRITE_ENABLE_GREEN),
			std::pair<std::string, uint32>("BLUE",						RS_COLOR_WRITE_ENABLE_BLUE),
			std::pair<std::string, uint32>("ALPHA",						RS_COLOR_WRITE_ENABLE_ALPHA),

			std::pair<std::string, uint32>("ALL",						RS_COLOR_WRITE_ENABLE_ALL),
		};

		static std::pair<std::string, uint32> FillModeEnum[] = 
		{
			std::pair<std::string, uint32>("WIREFRAME",					RS_FILL_WIREFRAME),
			std::pair<std::string, uint32>("SOLID",						RS_FILL_SOLID),
		};

		static std::pair<std::string, uint32> CullModeEnum[] = 
		{
			std::pair<std::string, uint32>("NONE",						RS_CULL_NONE),
			std::pair<std::string, uint32>("FRONT",						RS_CULL_FRONT),
			std::pair<std::string, uint32>("BACK",						RS_CULL_BACK),
		};

		static std::pair<std::string, uint32> DepthWriteEnum[] = 
		{
			std::pair<std::string, uint32>("ZERO",						RS_DEPTH_WRITE_MASK_ZERO),
			std::pair<std::string, uint32>("ALL",						RS_DEPTH_WRITE_MASK_ALL),

		};
		
		static std::pair<std::string, uint32> CompFuncEnum[] = 
		{
			std::pair<std::string, uint32>("NEVER",						RS_COMPARISON_NEVER),
			std::pair<std::string, uint32>("LESS",						RS_COMPARISON_LESS),
			std::pair<std::string, uint32>("EQUAL",						RS_COMPARISON_EQUAL),
			std::pair<std::string, uint32>("LESS_EQUAL",				RS_COMPARISON_LESS_EQUAL),
			std::pair<std::string, uint32>("GREATER",					RS_COMPARISON_GREATER),
			std::pair<std::string, uint32>("NOT_EQUAL",					RS_COMPARISON_NOT_EQUAL),
			std::pair<std::string, uint32>("GREATER_EQUAL",				RS_COMPARISON_GREATER_EQUAL),
			std::pair<std::string, uint32>("ALWAYS",					RS_COMPARISON_ALWAYS),


		};


		static std::pair<std::string, uint32> StencilOPEnum[] = 
		{
			std::pair<std::string, uint32>("KEEP",						RS_STENCIL_OP_KEEP),
			std::pair<std::string, uint32>("ZERO",						RS_STENCIL_OP_ZERO),
			std::pair<std::string, uint32>("REPLACE",					RS_STENCIL_OP_REPLACE),
			std::pair<std::string, uint32>("INCR_SAT",					RS_STENCIL_OP_INCR_SAT),
			std::pair<std::string, uint32>("DECR_SAT",					RS_STENCIL_OP_DECR_SAT),
			std::pair<std::string, uint32>("INVERT",					RS_STENCIL_OP_INVERT),
			std::pair<std::string, uint32>("INCR",						RS_STENCIL_OP_INCR),
			std::pair<std::string, uint32>("DECR",						RS_STENCIL_OP_DECR),

		};


		RenderStateParser::RenderStateParser(BaseParser* parent, std::function<void (const std::string&)> logger) : BaseParser(parent, logger)
		{
		}

		RenderStateParser::~RenderStateParser(void)
		{
		}
		bool RenderStateParser::Parse(Lexer* lexer)
		{
			Token token = lexer->NextToken();

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

		bool RenderStateParser::ParseState(Lexer* lexer)
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

			name							= token.str;
			token							= lexer->NextToken();
			
			if(token.str != "=")
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			token							= lexer->NextToken();
			if(token.type != Token::token_id && token.type != Token::token_number &&token.str != "{")
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}

			std::string value;

			int line = token.line;

			if(token.str == "{")
			{
				if(false == ParseVec4(lexer, value))
				{
					token = lexer->CurToken();
					Error(token.line, "unexpected token: '" + token.str + "'");
					return false;
				}
				token							= lexer->CurToken();
			}
			else
			{
				value = token.str;
				token							= lexer->NextToken();
			}
			
			if(false == SetState(line, name, value))
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
		bool RenderStateParser::SetState(int line ,const std::string& name, const std::string& value)
		{
			if(ValidateEnumValue(name, StateList) == false)
			{
				Error(line, "undefined render state: '" + name + "'");
				return false;
			}

			return true;
		}
	}
}

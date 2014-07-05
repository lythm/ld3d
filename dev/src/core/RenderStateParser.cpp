#include "core_pch.h"
#include "core/RenderStateParser.h"
#include "core/Sys_Graphics.h"
#include "core/RenderState.h"

namespace ld3d
{
	namespace material_script
	{
		static char* StateList[] = 
		{
			"BlendFactor", 
			"BlendEnable", 
			"BlendAlphaOP", 
			"BlendRGBOP", 
			"BlendSrcRGB", 
			"BlendDstRGB", 
			"BlendSrcAlpha", 
			"BlendDstAlpha",
			"ColorWrite", 
			"FillMode", 
			"CullMode", 
			
			"FrontFace", 
			"DepthBias", 
			"DepthBiasClamp", 
			"SlopScaledDepthBias",
			"DepthClipEnable", 
			"DepthEnable", 
			"DepthWriteMask", 
			"DepthFunc",  
			"StencilEnable", 
			"FrontFaceStencilFailOP", 
			"FrontFaceStencilDepthFailOP", 
			"FrontFaceStencilPassOP", 
			"FrontFaceStencilFunc",
			"BackFaceStencilFailOP", 
			"BackFaceStencilDepthFailOP", 
			"BackFaceStencilPassOP", 
			"BackFaceStencilFunc",
			"FrontFaceStencilWriteMask", 
			"FrontFaceStencilReadMask",
			"BackFaceStencilWriteMask", 
			"BackFaceStencilReadMask",
			"FrontFaceStencilRef", 
			"BackFaceStencilRef",
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
//			std::pair<std::string, uint32>("SRC1_COLOR",				RS_BLEND_SRC1_COLOR),
//			std::pair<std::string, uint32>("INV_SRC1_COLOR",			RS_BLEND_INV_SRC1_COLOR),
//			std::pair<std::string, uint32>("SRC1_ALPHA",				RS_BLEND_SRC1_ALPHA),
//			std::pair<std::string, uint32>("INV_SRC1_ALPHA",			RS_BLEND_INV_SRC1_ALPHA),

		};
		static std::pair<std::string, uint32> BlendOPEnum[] = 
		{
			std::pair<std::string, uint32>("ADD",						RS_BLEND_OP_ADD),
			std::pair<std::string, uint32>("SUBTRACT",					RS_BLEND_OP_SUBTRACT),
			std::pair<std::string, uint32>("REV_SUBTRACT",				RS_BLEND_OP_REV_SUBTRACT),
			std::pair<std::string, uint32>("MIN",						RS_BLEND_OP_MIN),

			std::pair<std::string, uint32>("MAX",						RS_BLEND_OP_MAX),

		};

		static std::pair<std::string, uint32> FrontFaceEnum[] = 
		{
			std::pair<std::string, uint32>("CW",						RS_CW),
			std::pair<std::string, uint32>("CCW",						RS_CCW),
		};

		static std::pair<std::string, uint32> ColorWriteEnum[] = 
		{
			/*std::pair<std::string, uint32>("RED",						RS_COLOR_WRITE_ENABLE_RED),
			std::pair<std::string, uint32>("GREEN",						RS_COLOR_WRITE_ENABLE_GREEN),
			std::pair<std::string, uint32>("BLUE",						RS_COLOR_WRITE_ENABLE_BLUE),
			std::pair<std::string, uint32>("ALPHA",						RS_COLOR_WRITE_ENABLE_ALPHA),*/

			std::pair<std::string, uint32>("Zero",						RS_COLOR_WRITE_ENABLE_ZERO),
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
			std::pair<std::string, uint32>("LEQUAL",					RS_COMPARISON_LESS_EQUAL),
			std::pair<std::string, uint32>("GREATER",					RS_COMPARISON_GREATER),
			std::pair<std::string, uint32>("NEQUAL",					RS_COMPARISON_NOT_EQUAL),
			std::pair<std::string, uint32>("GEQUAL",					RS_COMPARISON_GREATER_EQUAL),
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


		RenderStateParser::RenderStateParser(BaseParser* parent, const Logger& logger) : BaseParser(parent, logger)
		{
			_BlendFactor						= math::Vector4(0, 0, 0, 1);
			_BlendEnable						= false;
			_BlendAlphaOP						= RS_BLEND_OP_ADD;
			_BlendRGBOP							= RS_BLEND_OP_ADD;
			_BlendSrcRGB						= RS_BLEND_ONE;
			_BlendDstRGB						= RS_BLEND_ONE;;
			_BlendSrcAlpha						= RS_BLEND_ONE;;
			_BlendDstAlpha						= RS_BLEND_ONE;;
			_ColorWrite							= RS_COLOR_WRITE_ENABLE_ALL;
			_FillMode							= RS_FILL_SOLID;
			_CullMode							= RS_CULL_BACK;
			_FrontFace							= RS_CW;
			_DepthClipEnable					= false;
			_DepthEnable						= true;
			_DepthWriteMask						= RS_DEPTH_WRITE_MASK_ALL;
			_DepthFunc							= RS_COMPARISON_LESS_EQUAL;
			_StencilEnable						= false;
			_FrontFaceStencilFailOP				= RS_STENCIL_OP_KEEP;
			_FrontFaceStencilDepthFailOP		= RS_STENCIL_OP_KEEP;
			_FrontFaceStencilPassOP				= RS_STENCIL_OP_KEEP;
			_FrontFaceStencilFunc				= RS_COMPARISON_ALWAYS;

			_BackFaceStencilFailOP				= RS_STENCIL_OP_KEEP;
			_BackFaceStencilDepthFailOP			= RS_STENCIL_OP_KEEP;
			_BackFaceStencilPassOP				= RS_STENCIL_OP_KEEP;
			_BackFaceStencilFunc				= RS_COMPARISON_ALWAYS;

			_FrontFaceStencilWriteMask			= 0xffffffff;
			_FrontFaceStencilReadMask			= 0xffffffff;
			_BackFaceStencilWriteMask			= 0xffffffff;
			_BackFaceStencilReadMask			= 0xffffffff;

			_FrontFaceStencilRef				= 0;
			_BackFaceStencilRef					= 0;
		}

		RenderStateParser::~RenderStateParser(void)
		{
		}
		bool RenderStateParser::Parse(Lexer* lexer, const boost::filesystem::path& dir)
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

			//"BlendFactor", 
			if(str_i_cmp(name, "BlendFactor"))
			{
				if(ParseVec4(value, _BlendFactor))
				{
					return true;
				}
			}

			//"BlendEnable", 
			if(str_i_cmp(name, "BlendEnable"))
			{
				if(ParseBool(value, _BlendEnable))
				{
					return true;
				}
			}

			//"BlendAlphaOP"
			if(str_i_cmp(name, "BlendAlphaOP"))
			{
				if(ParseEnum(value, (uint32&)_BlendAlphaOP, BlendOPEnum))
				{
					return true;
				}
			}
			
			//"BlendRGBOP"
			if(str_i_cmp(name, "BlendRGBOP"))
			{
				if(ParseEnum(value, (uint32&)_BlendRGBOP, BlendOPEnum))
				{
					return true;
				}
			}

			//"BlendSrcRGB"
			if(str_i_cmp(name, "BlendSrcRGB"))
			{
				if(ParseEnum(value, (uint32&)_BlendSrcRGB, BlendEnum))
				{
					return true;
				}
			}
			
			//"BlendDstRGB"
			if(str_i_cmp(name, "BlendDstRGB"))
			{
				if(ParseEnum(value, (uint32&)_BlendDstRGB, BlendEnum))
				{
					return true;
				}
			}

			//"BlendSrcAlpha"
			if(str_i_cmp(name, "BlendSrcAlpha"))
			{
				if(ParseEnum(value, (uint32&)_BlendSrcAlpha, BlendEnum))
				{
					return true;
				}
			}
			//"BlendDstAlpha",
			if(str_i_cmp(name, "BlendDstAlpha"))
			{
				if(ParseEnum(value, (uint32&)_BlendDstAlpha, BlendEnum))
				{
					return true;
				}
			}
			//"ColorWrite"
			if(str_i_cmp(name, "ColorWrite"))
			{
				if(ParseEnum(value, (uint32&)_ColorWrite, ColorWriteEnum))
				{
					return true;
				}
			}


			//"FillMode"
			if(str_i_cmp(name, "FillMode"))
			{
				if(ParseEnum(value, (uint32&)_FillMode, FillModeEnum))
				{
					return true;
				}
			}
			
			//"CullMode" 
			if(str_i_cmp(name, "CullMode"))
			{
				if(ParseEnum(value, (uint32&)_CullMode, CullModeEnum))
				{
					return true;
				}
			}
			
			//"FrontFace"
			if(str_i_cmp(name, "FrontFace"))
			{
				if(ParseEnum(value, (uint32&)_FrontFace, FrontFaceEnum))
				{
					return true;
				}
			}
			
			//"DepthBias"
			/*if(str_i_cmp(name, "DepthBias"))
			{
				if(ParseBool(value, DepthBias))
				{
					return true;
				}
			}*/
			
			//, "DepthBiasClamp", "SlopScaledDepthBias",


			//"DepthClipEnable"
			if(str_i_cmp(name, "DepthClipEnable"))
			{
				if(ParseBool(value, _DepthClipEnable))
				{
					return true;
				}
			}
			
			//"DepthEnable"
			if(str_i_cmp(name, "DepthEnable"))
			{
				if(ParseBool(value, _DepthEnable))
				{
					return true;
				}
			}
			//"DepthWriteMask"
			if(str_i_cmp(name, "DepthWriteMask"))
			{
				if(ParseEnum(value, (uint32&)_DepthWriteMask, DepthWriteEnum))
				{
					return true;
				}
			}
			
			//"DepthFunc"
			if(str_i_cmp(name, "DepthFunc"))
			{
				if(ParseEnum(value, (uint32&)_DepthFunc, CompFuncEnum))
				{
					return true;
				}
			}
			//"StencilEnable"
			if(str_i_cmp(name, "StencilEnable"))
			{
				if(ParseBool(value, _StencilEnable))
				{
					return true;
				}
			}
			//"FrontFaceStencilFailOP"
			if(str_i_cmp(name, "FrontFaceStencilFailOP"))
			{
				if(ParseEnum(value, (uint32&)_FrontFaceStencilFailOP, StencilOPEnum))
				{
					return true;
				}
			}
			//"FrontFaceStencilDepthFailOP"
			if(str_i_cmp(name, "FrontFaceStencilDepthFailOP"))
			{
				if(ParseEnum(value, (uint32&)_FrontFaceStencilDepthFailOP, StencilOPEnum))
				{
					return true;
				}
			}
			//"FrontFaceStencilPassOP"
			if(str_i_cmp(name, "FrontFaceStencilPassOP"))
			{
				if(ParseEnum(value, (uint32&)_FrontFaceStencilPassOP, StencilOPEnum))
				{
					return true;
				}
			}
			//"FrontFaceStencilFunc"
			if(str_i_cmp(name, "FrontFaceStencilFunc"))
			{
				if(ParseEnum(value, (uint32&)_FrontFaceStencilFunc, CompFuncEnum))
				{
					return true;
				}
			}
			
			//"BackFaceStencilFailOP"
			if(str_i_cmp(name, "BackFaceStencilFailOP"))
			{
				if(ParseEnum(value, (uint32&)_BackFaceStencilFailOP, StencilOPEnum))
				{
					return true;
				}
			}
			//"BackFaceStencilDepthFailOP"
			if(str_i_cmp(name, "BackFaceStencilDepthFailOP"))
			{
				if(ParseEnum(value, (uint32&)_BackFaceStencilDepthFailOP, StencilOPEnum))
				{
					return true;
				}
			}
			//"BackFaceStencilPassOP"
			if(str_i_cmp(name, "BackFaceStencilPassOP"))
			{
				if(ParseEnum(value, (uint32&)_BackFaceStencilPassOP, StencilOPEnum))
				{
					return true;
				}
			}
			//"BackFaceStencilFunc",
			if(str_i_cmp(name, "BackFaceStencilFunc"))
			{
				if(ParseEnum(value, (uint32&)_BackFaceStencilFunc, CompFuncEnum))
				{
					return true;
				}
			}

			//"FrontFaceStencilWriteMask"
			if(str_i_cmp(name, "FrontFaceStencilWriteMask"))
			{
				if(ParseInt(value, _FrontFaceStencilWriteMask))
				{
					return true;
				}
			}
			//"FrontFaceStencilReadMask"
			if(str_i_cmp(name, "FrontFaceStencilReadMask"))
			{
				if(ParseInt(value, _FrontFaceStencilReadMask))
				{
					return true;
				}
			}

			//"BackFaceStencilWriteMask"
			if(str_i_cmp(name, "BackFaceStencilWriteMask"))
			{
				if(ParseInt(value, _BackFaceStencilWriteMask))
				{
					return true;
				}
			}
			//"BackFaceStencilReadMask"
			if(str_i_cmp(name, "BackFaceStencilReadMask"))
			{
				if(ParseInt(value, _BackFaceStencilReadMask))
				{
					return true;
				}
			}


			// "FrontFaceStencilRef"
			if(str_i_cmp(name, "FrontFaceStencilRef"))
			{
				if(ParseInt(value, _FrontFaceStencilRef))
				{
					return true;
				}
			}
			
			//"BackFaceStencilRef"
			if(str_i_cmp(name, "BackFaceStencilRef"))
			{
				if(ParseInt(value, _BackFaceStencilRef))
				{
					return true;
				}
			}

			Error(line, "invalid value: '" + value + "'");
			return false;
		}
		RenderStatePtr	RenderStateParser::CreateObject(Sys_GraphicsPtr pGraphics)
		{
			RenderStatePtr pState = pGraphics->CreateRenderState();

			pState->Begin();
			{
				pState->SetBlendFactor(_BlendFactor);
				pState->SetBlendEnable(_BlendEnable);
				pState->SetBlendOp(_BlendRGBOP, _BlendAlphaOP);
				pState->SetBlendVariable(_BlendSrcRGB, _BlendDstRGB, _BlendSrcAlpha, _BlendDstAlpha);

				pState->SetColorWrite(_ColorWrite);
				pState->SetFillMode(_FillMode);
				pState->SetCullMode(_CullMode);
				pState->SetFrontFace(_FrontFace);
				//pState->SetDepthBias(uint32 val);
				//pState->SetDepthBiasClamp(float val);
				//pState->SetSlopeScaledDepthBias(float val);
				pState->SetDepthClipEnable(_DepthClipEnable);
				pState->SetDepthEnable(_DepthEnable);
				pState->SetDepthWriteMask(_DepthWriteMask);
				pState->SetDepthFunc(_DepthFunc);
				pState->SetStencilEnable(_StencilEnable);
				pState->SetFrontFaceStencilOP(_FrontFaceStencilFailOP, _FrontFaceStencilDepthFailOP, _FrontFaceStencilPassOP);
				pState->SetBackFaceStencilOP(_BackFaceStencilFailOP, _BackFaceStencilDepthFailOP, _BackFaceStencilPassOP);
				pState->SetFrontFaceStencilWriteMask(_FrontFaceStencilWriteMask);
				pState->SetBackFaceStencilWriteMask(_BackFaceStencilWriteMask);
				pState->SetFrontFaceStencilFunc(_FrontFaceStencilFunc, _FrontFaceStencilRef, _FrontFaceStencilReadMask);
				pState->SetBackFaceStencilFunc(_BackFaceStencilFunc, _BackFaceStencilRef, _BackFaceStencilReadMask);

			}
			pState->End();

			return pState;
		}
	}
}

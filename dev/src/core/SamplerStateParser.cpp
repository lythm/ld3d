#include "core_pch.h"
#include "core/SamplerStateParser.h"
#include "core/Sys_Graphics.h"
namespace ld3d
{
	namespace material_script
	{
		static char* StateList[] = 
		{
			"AddressModeU", "AddressModeV", "AddressModeW", "Filter", "MinLod", "MaxLod", /*"MipLodBias",*/ "MaxAnisotropy", "BorderColor",
		};

		static std::pair<std::string, uint32> AddressModeEnum[] = 
		{
			std::pair<std::string, uint32>("REPEAT",							SamplerState::AM_REPEAT),
			std::pair<std::string, uint32>("MIRROR",							SamplerState::AM_MIRROR),
			std::pair<std::string, uint32>("CLAMP",								SamplerState::AM_CLAMP),
			std::pair<std::string, uint32>("BORDER",							SamplerState::AM_BORDER),
		};
		
		static std::pair<std::string, uint32> FilterEnum[] = 
		{
			std::pair<std::string, uint32>("MIN_LINEAR_MAG_POINT",				SamplerState::FILTER_MIN_LINEAR_MAG_POINT),
			std::pair<std::string, uint32>("MIN_POINT_MAG_LINEAR",				SamplerState::FILTER_MIN_POINT_MAG_LINEAR),
			std::pair<std::string, uint32>("MIN_MAG_POINT",						SamplerState::FILTER_MIN_MAG_POINT),
			std::pair<std::string, uint32>("MIN_MAG_LINEAR",					SamplerState::FILTER_MIN_MAG_LINEAR),
			
			std::pair<std::string, uint32>("MIN_MAG_MIP_POINT",					SamplerState::FILTER_MIN_MAG_MIP_POINT),
			std::pair<std::string, uint32>("MIN_MAG_POINT_MIP_LINEAR",			SamplerState::FILTER_MIN_MAG_POINT_MIP_LINEAR),
			std::pair<std::string, uint32>("MIN_POINT_MAG_LINEAR_MIP_POINT",	SamplerState::FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT),
			std::pair<std::string, uint32>("MIN_POINT_MAG_MIP_LINEAR",			SamplerState::FILTER_MIN_POINT_MAG_MIP_LINEAR),
			std::pair<std::string, uint32>("MIN_LINEAR_MAG_MIP_POINT",			SamplerState::FILTER_MIN_LINEAR_MAG_MIP_POINT),
			std::pair<std::string, uint32>("MIN_LINEAR_MAG_POINT_MIP_LINEAR",	SamplerState::FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR),
			std::pair<std::string, uint32>("MIN_MAG_LINEAR_MIP_POINT",			SamplerState::FILTER_MIN_MAG_LINEAR_MIP_POINT),
			std::pair<std::string, uint32>("MIN_MAG_MIP_LINEAR",				SamplerState::FILTER_MIN_MAG_MIP_LINEAR),
			std::pair<std::string, uint32>("ANISOTROPIC",						SamplerState::FILTER_ANISOTROPIC),
			
		};

		SamplerStateParser::SamplerStateParser(BaseParser* parent, const Logger& logger) : BaseParser(parent, logger)
		{

			_AddressModeU			= SamplerState::AM_REPEAT;
			_AddressModeV			= SamplerState::AM_REPEAT;
			_AddressModeW			= SamplerState::AM_REPEAT;

			_Filter					= SamplerState::FILTER_MIN_MAG_MIP_LINEAR;
			_MinLod					= -1000;
			_MaxLod					= 1000;
			_MaxAnisotropy			= 0;
			_BorderColor			= math::Vector4(0, 0, 0, 1.0f);
		}


		SamplerStateParser::~SamplerStateParser(void)
		{
		}
		bool SamplerStateParser::Parse(Lexer* lexer, const boost::filesystem::path& dir)
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
		bool SamplerStateParser::ParseState(Lexer* lexer)
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
		bool SamplerStateParser::SetState(int line ,const std::string& name, const std::string& value)
		{
			if(ValidateEnumValue(name, StateList) == false)
			{
				Error(line, "undefined sampler state: '" + name + "'");
				return false;
			}

			if(str_i_cmp(name, "AddressModeU"))
			{
				if(ParseEnum(value, (uint32&)_AddressModeU, AddressModeEnum))
				{
					return true;
				}

			}
			if(str_i_cmp(name, "AddressModeV"))
			{
				if(ParseEnum(value, (uint32&)_AddressModeV, AddressModeEnum))
				{
					return true;
				}

			}

			if(str_i_cmp(name, "AddressModeW"))
			{
				if(ParseEnum(value, (uint32&)_AddressModeW, AddressModeEnum))
				{
					return true;
				}

			}
			

			if(str_i_cmp(name, "Filter"))
			{
				if(ParseEnum(value, (uint32&)_Filter, FilterEnum))
				{
					return true;
				}
			}

			if(str_i_cmp(name, "MinLod"))
			{
				if(ParseFloat(value, _MinLod) == true)
				{
					return true;
				}
			}

			if(str_i_cmp(name, "MaxLod"))
			{
				if(ParseFloat(value, _MaxLod) == true)
				{
					return true;
				}

			}

			/*if(str_i_cmp(name, "MipLodBias"))
			{
				if(IsInt(value))
				{
					_MipLodBias = strtol(value.c_str(), nullptr, 10);
					return true;
				}
			}*/

			if(str_i_cmp(name, "MaxAnisotropy"))
			{
				if(ParseInt(value, (int&)_MaxAnisotropy))
				{
					return true;
				}
			}
			
			if(str_i_cmp(name, "BorderColor"))
			{
				if(ParseVec4(value, _BorderColor))
				{
					return true;
				}
			}

			Error(line, "invalid value: '" + value + "'");
			return false;
		}
		SamplerStatePtr	SamplerStateParser::CreateObject(Sys_GraphicsPtr pGraphics)
		{
			SamplerStatePtr pSampler = pGraphics->CreateSampler();

			pSampler->SetAddressMode(_AddressModeU, _AddressModeV, _AddressModeW);
			pSampler->SetBorderColor(math::Color4(_BorderColor.x, _BorderColor.y, _BorderColor.z, _BorderColor.w));
			pSampler->SetFilter(_Filter);
			pSampler->SetLod(_MinLod, _MaxLod);
			pSampler->SetMaxAnisotropy(_MaxAnisotropy);

			return pSampler;
		}
	}
}

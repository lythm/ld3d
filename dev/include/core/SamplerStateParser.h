#pragma once

#include "core/MaterialBaseParser.h"
#include "core/SamplerState.h"

namespace ld3d
{
	namespace material_script
	{
		class SamplerStateParser : public BaseParser
		{
		public:
			SamplerStateParser(BaseParser* parent, Logger& logger = Logger());
			virtual ~SamplerStateParser(void);

			bool												Parse(Lexer* lexer, const boost::filesystem::path& dir = "./");

			SamplerStatePtr										CreateObject(Sys_GraphicsPtr pGraphics);
		private:
			bool												ParseState(Lexer* lexer);

			bool												SetState(int line, const std::string& name, const std::string& value);
			
		private:

			SamplerState::ADDRESS_MODE							_AddressModeU;
			SamplerState::ADDRESS_MODE							_AddressModeV;
			SamplerState::ADDRESS_MODE							_AddressModeW;

			SamplerState::FILTER								_Filter;
			float												_MinLod;
			float												_MaxLod;
			//uint32												_MipLodBias;
			uint32												_MaxAnisotropy;
			math::Vector4										_BorderColor;
		};
	}
}
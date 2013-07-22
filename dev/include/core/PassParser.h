#pragma once
#include "core/MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		class PassParser  : public BaseParser
		{
			typedef std::pair<std::string, std::string>			SamplerLink;
		public:
			PassParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~PassParser(void);

			bool												Parse(Lexer* lexer);

			MaterialPassPtr										CreateObject(Sys_Graphics2Ptr pGraphics);
		private:
			bool												ParseFunctionCall(Lexer* lexer);
			bool												SetState(const std::vector<Token>& func);
		private:
			std::string											_VertexShader;
			std::string											_PixelShader;
			std::string											_GeometryShader;

			std::string											_RenderState;
			std::vector<SamplerLink>							_SamplerLink;

		};


	}
}
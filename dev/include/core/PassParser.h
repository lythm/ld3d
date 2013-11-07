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
			PassParser(BaseParser* parent, Logger& logger = Logger());
			virtual ~PassParser(void);

			bool												Parse(Lexer* lexer, const boost::filesystem::path& dir = "./");

			MaterialPassPtr										CreateObject(Sys_GraphicsPtr pGraphics);
		private:
			bool												ParseFunctionCall(Lexer* lexer);
			bool												SetState(const std::vector<Token>& func);
		private:
			boost::filesystem::path								_VertexShader;
			std::string											_VertexShaderEntry;
			boost::filesystem::path								_PixelShader;
			std::string											_PixelShaderEntry;
			boost::filesystem::path								_GeometryShader;
			std::string											_GeometryShaderEntry;

			std::string											_RenderState;
			std::vector<SamplerLink>							_SamplerLink;

			boost::filesystem::path								m_rootDir;

		};
	}
}
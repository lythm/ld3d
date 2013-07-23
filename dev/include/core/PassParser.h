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

			bool												Parse(Lexer* lexer, const boost::filesystem::path& dir = "./");

			MaterialPassPtr										CreateObject(Sys_GraphicsPtr pGraphics);
		private:
			bool												ParseFunctionCall(Lexer* lexer);
			bool												SetState(const std::vector<Token>& func);
		private:
			boost::filesystem::path								_VertexShader;
			boost::filesystem::path								_PixelShader;
			boost::filesystem::path								_GeometryShader;

			std::string											_RenderState;
			std::vector<SamplerLink>							_SamplerLink;

			boost::filesystem::path								m_rootDir;

		};
	}
}
#include "core_pch.h"
#include "core/MaterialParser.h"
#include "core_utils.h"
#include "core/SamplerStateParser.h"
#include "core/RenderStateParser.h"
#include "core/TechniqueParser.h"
#include "core/PassParser.h"
#include "core/Material.h"
namespace ld3d
{
	
	namespace material_script
	{
		MaterialParser::MaterialParser(BaseParser* parent, Logger& logger) : BaseParser(parent, logger)
		{
		}
		MaterialParser::~MaterialParser()
		{

		}
		bool MaterialParser::Parse(Lexer* lexer, const boost::filesystem::path& dir)
		{
			m_rootDir = dir;
			Token token = lexer->NextToken();

			while(true)
			{
				switch(token.type)
				{
				case Token::token_misc:
					if(token.str != ";")
					{
						Error(token.line, "unexpected token: '" + token.str + "'");
						return false;
					}
					
					token = lexer->SkipToken(token);
					break;

				case Token::token_id:
					if(false == ParseIdentifier(lexer))
					{
						return false;
					}

					token = lexer->CurToken();
					break;
				case Token::token_eof:
					return true;
				default:
					Error(token.line, "unexpected token: '" + token.str + "'");
					token = lexer->NextToken();
					break;
				}
			}

			Error(-1, "====== failed. ======");
			return false;
		}
		bool MaterialParser::ParseIdentifier(Lexer* lexer)
		{
			Token token						= lexer->CurToken();

			if(str_i_cmp(token.str, "SamplerState"))
			{
				SamplerStateParserPtr pParser = std::make_shared<SamplerStateParser>(this, m_logger);

				if(pParser->Parse(lexer) == false)
				{
					return false;
				}

				m_members.push_back(pParser);
				return true;
			}


			if(str_i_cmp(token.str, "RenderState"))
			{
				RenderStateParserPtr pParser = std::make_shared<RenderStateParser>(this, m_logger);

				if(pParser->Parse(lexer) == false)
				{
					return false;
				}

				m_members.push_back(pParser);
				return true;
			}


			if(str_i_cmp(token.str, "Technique"))
			{
				TechniqueParserPtr pParser = std::make_shared<TechniqueParser>(this, m_logger);

				if(pParser->Parse(lexer, m_rootDir) == false)
				{
					return false;
				}

				m_members.push_back(pParser);
				return true;
			}
			Error(token.line, "unexpected token: '" + token.str + "'");
			return false;
		}
		MaterialPtr MaterialParser::CreateObject(Sys_GraphicsPtr pGraphics)
		{
			MaterialPtr pMaterial = std::make_shared<Material>(pGraphics);
			for(auto v : m_members)
			{
				TechniqueParserPtr pParse = std::dynamic_pointer_cast<TechniqueParser>(v);
				if(pParse == nullptr)
				{
					continue;
				}

				MaterialTechPtr pTech = pParse->CreateObject(pGraphics);
				if(pTech == nullptr)
				{
					Error(0, "failed to create technique: '" + v->Name() + "'");
					pMaterial->Release();
					return nullptr;
				}

				pMaterial->AddTech(pTech);
			}

			return pMaterial;
		}
	}
}

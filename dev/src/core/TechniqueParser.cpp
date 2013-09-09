#include "core_pch.h"
#include "core/TechniqueParser.h"
#include "core/PassParser.h"
#include "core/MaterialTech.h"
#include "core/MaterialPass.h"

namespace ld3d
{
	namespace material_script
	{
		
		TechniqueParser::TechniqueParser(BaseParser* parent, Logger& logger) : BaseParser(parent, logger)
		{
		}


		TechniqueParser::~TechniqueParser(void)
		{
		}
		bool TechniqueParser::Parse(Lexer* lexer, const boost::filesystem::path& dir)
		{
			m_rootDir = dir;
			Token token = lexer->NextToken();

			if(token.str == "}")
			{
				return true;
			}

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
				if(ParsePass(lexer) == false)
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
		bool TechniqueParser::ParsePass(Lexer* lexer)
		{
			Token token = lexer->CurToken();
			if(token.str == "}")
			{
				return true;
			}

			if(token.type != Token::token_id)
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}
			if(str_i_cmp(token.str, "Pass") == false)
			{
				Error(token.line, "unexpected token: '" + token.str + "'");
				return false;
			}
			token = lexer->NextToken();
			
			PassParserPtr pPassParser = std::make_shared<PassParser>(this, m_logger);

			if(pPassParser->Parse(lexer, m_rootDir) == false)
			{
				return false;
			}

			m_members.push_back(pPassParser);

			return true;
		}
		MaterialTechPtr TechniqueParser::CreateObject(Sys_GraphicsPtr pGraphics)
		{
			MaterialTechPtr pTech = std::make_shared<MaterialTech>(m_name);

			for(auto v : m_members)
			{
				PassParserPtr pParser = std::dynamic_pointer_cast<PassParser>(v);
				
				MaterialPassPtr pPass = pParser->CreateObject(pGraphics);
				if(pPass == nullptr)
				{
					Error(0, "failed to create pass: '" + pParser->Name() + "'");

					pTech->Release();
					return nullptr;
				}

				pTech->AddPass(pPass);
			}

			return pTech;
		}
	}
}

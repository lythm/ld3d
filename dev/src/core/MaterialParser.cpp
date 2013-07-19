#include "core_pch.h"
#include "..\..\include\core\MaterialParser.h"
#include "core_utils.h"
#include "core/SamplerStateParser.h"
#include "core/RenderStateParser.h"
#include "core/TechniqueParser.h"
#include "core/PassParser.h"

namespace ld3d
{
	namespace material_script
	{

		MaterialParser::MaterialParser(std::function<void (const std::string&)> logger)
		{
			m_logger = logger;
			_reset("");

		}

		MaterialParser::~MaterialParser(void)
		{

		}

		bool MaterialParser::Parse(const std::string& src, const std::vector<std::string>& const_list)
		{
			_reset(src);

			m_root.type = "__root__";
			m_root.value = "";
			m_root.parent = nullptr;


			for(auto v : const_list)
			{
				ObjectMetaData consts;
				consts.line = -1;
				consts.type = "__constant__";
				consts.parent = &m_root;
				consts.value = v;
				m_root.members.push_back(consts);
			}

			TypeInfo passType;
			passType.name = "SamplerState";
			passType.value_type = "__string__";
			passType.members.push_back(std::make_pair("__assign__", "AddressModeU"));
			passType.members.push_back(std::make_pair("__assign__", "AddressModeV"));
			passType.members.push_back(std::make_pair("__assign__", "AddressModeW"));
			passType.members.push_back(std::make_pair("__function_call__", "SetVertexShader"));

			m_typeInfoList.push_back(passType);

			Token token = m_lexer.NextToken();

			while(NoError())
			{
				switch(token.type)
				{
				case Token::token_misc:
					token = _parse_misc();
					break;

				case Token::token_id:
					token = _parse_identifier(m_root);
					break;
				case Token::token_eof:
					return ParseObjectTree(&m_root);
				default:
					_error(token.line, "unexpected token: '" + token.str + "'");
					token = m_lexer.NextToken();
					break;
				}
			}

			_error(-1, "====== failed. ======");
			return false;
		}
		void MaterialParser::_reset(const std::string& src)
		{
			m_root.members.clear();
			m_bNoError = true;
			m_lexer.Reset(src);

			m_builtInTypeInfoList.clear();
			_init_built_in_type_info();
		}
		void MaterialParser::_error(int line, const std::string& msg)
		{
			if(m_logger)
			{
				m_logger("(" + std::to_string(line + 1) + "): " + msg);
			}

			m_bNoError = false;
		}
		Token MaterialParser::_parse_identifier(ObjectMetaData& obj)
		{
			Token token = m_lexer.CurToken();
			Token next_token				= m_lexer.NextToken();

			if(next_token.type == Token::token_id)
			{
				ObjectMetaData child;

				if(_create_object(child, token.str, next_token.str, &obj) == false)
				{
					_error(token.line, "undefined symbol: " + token.str);
					return next_token;
				}
				child.line = next_token.line;

				if(_already_defined(child.value, obj))
				{
					_error_already_defined(next_token.line, child);
					return m_lexer.NextToken();;
				}

				next_token = _parse_object(child);

				obj.members.push_back(child);
				return next_token;
			}
			if(next_token.type == Token::token_misc)
			{
				if(next_token.str == "(")
				{
					if(_validate_member(obj.typeinfo, "__function_call__", token.str) == false)
					{
						_error(token.line, "undefined symbol: " + token.str);
						return next_token;
					}

					ObjectMetaData child;
					child.type = "__function_call__";
					child.value = token.str;
					child.parent = &obj;
					child.line = next_token.line;
					next_token = _parse_function_call(child);
					obj.members.push_back(child);
					return next_token;
				}
				if(next_token.str == "=")
				{
					if(_validate_member(obj.typeinfo, "__assign__", token.str) == false)
					{
						_error(token.line, "undefined symbol: " + token.str);
						return next_token;
					}
					ObjectMetaData child;
					child.type = "__assign__";
					child.value = token.str;
					child.parent = &obj;
					child.line = next_token.line;

					if(_already_defined(child.value, obj))
					{

						_error_already_defined(next_token.line, child);
						return m_lexer.NextToken();;
					}

					next_token = _parse_expr_assign(child);
					obj.members.push_back(child);
					return next_token;
				}
			}

			if(token.type == Token::token_eof)
			{
				_error(token.line, "unexpected end of file.");
				return token;
			}

			_error(next_token.line, "unexpected token: '" + next_token.str + "'");
			return next_token;
		}
		Token MaterialParser::_parse_misc()
		{
			Token token = m_lexer.CurToken();

			if(token.str == ";")
			{
				return m_lexer.SkipToken(token);
			}

			_error(token.line, "unexpected token: '" + token.str + "'");

			return m_lexer.NextToken();
		}

		Token MaterialParser::_parse_object(ObjectMetaData& obj)
		{
			Token token = m_lexer.NextToken();

			if(token.str == "{")
			{
				token = m_lexer.NextToken();
				while(true)
				{
					if(token.type == Token::token_id)
					{
						token = _parse_identifier(obj);
						continue;
					}
					if(token.str == "}")
					{
						token = m_lexer.NextToken();

						if(token.str == ";")
						{
							while(token.str == ";")
							{
								token = m_lexer.NextToken();
							}
							return token;
						}
						return token;
					}

					break;
				}
			}

			if(token.type == Token::token_eof)
			{
				_error(token.line, "unexpected end of file.");
				return token;
			}
			_error(token.line, "unexpected token: '" + token.str + "'");
			return token;
		}
		Token MaterialParser::_parse_function_call(ObjectMetaData& obj)
		{
			Token token = m_lexer.NextToken();

			while(true)
			{
				if(token.type != Token::token_id && token.type != Token::token_number && token.type != Token::token_string && token.str != ")")
				{
					break;
				}

				if(token.str == ")")
				{
					token = m_lexer.NextToken();

					while(token.str == ";")
					{
						token = m_lexer.NextToken();
					}

					return token;
				}

				ObjectMetaData param;

				if(token.type == Token::token_id)
				{
					const ObjectMetaData* ref = _find_obj_ref(token.str, obj);
					if(ref == nullptr)
					{
						_error(token.line, "undefine symbol: " + token.str);
						return token;
					}

					param.type = "__object__";
				}
				if(token.type == Token::token_number)
				{
					param.type = "__number__";

				}
				if(token.type == Token::token_string)
				{
					param.type = "__string__";

				}
				param.value = token.str;
				param.parent = &obj;
				param.line = token.line;	
				obj.members.push_back(param);


				token = m_lexer.NextToken();
				if(token.str != "," && token.str != ")")
				{
					break;
				}

				if(token.str == ",")
				{
					token = m_lexer.NextToken();
				}
			}

			_error(token.line, "unexpected token: '" + token.str + "'");
			return token;
		}
		Token MaterialParser::_parse_expr_assign(ObjectMetaData& obj)
		{
			Token token = m_lexer.NextToken();

			if(token.type == Token::token_id)
			{
				const ObjectMetaData* ref = _find_obj_ref(token.str, obj);
				if(ref == nullptr)
				{
					_error(token.line, "undefine symbol: " + token.str);
					return token;
				}
				ObjectMetaData value;
				value.type = "__object__";
				value.value = token.str;
				value.parent = &obj;
				value.line = token.line;	
				obj.members.push_back(value);

				token = m_lexer.NextToken();
			}
			if(token.type == Token::token_number)
			{
				ObjectMetaData value;
				value.type = "__number__";
				value.value = token.str;
				value.parent = &obj;
				value.line = token.line;	
				obj.members.push_back(value);

				token = m_lexer.NextToken();
			}
			if(token.type == Token::token_string)
			{
				ObjectMetaData value;
				value.type = "__string__";
				value.value = token.str;
				value.parent = &obj;
				value.line = token.line;	
				obj.members.push_back(value);

				token = m_lexer.NextToken();
			}
			if(token.str == ";")
			{
				while(token.str == ";")
				{
					token = m_lexer.NextToken();
				}
				return token;
			}

			if(token.type == Token::token_eof)
			{
				_error(token.line, "unexpected end of file.");
				return token;
			}

			_error(token.line, "';' expected.");
			return token;
		}
		bool MaterialParser::_already_defined(const std::string& value, const ObjectMetaData& scope)
		{
			for(const auto & v : scope.members)
			{
				if(_stricmp(v.value.c_str(), value.c_str()) == 0)
				{
					return true;
				}
			}

			return false;
		}
		const ObjectMetaData* MaterialParser::_find_obj_ref(const std::string& name, const ObjectMetaData& scope)
		{
			const ObjectMetaData* parent = &scope;

			while(parent)
			{
				for(const auto & v : parent->members)
				{
					if(_stricmp(v.value.c_str(), name.c_str()) == 0)
					{
						return &v;
					}
				}
				parent = parent->parent;
			}

			return nullptr;
		}
		void MaterialParser::_error_already_defined(int line, const ObjectMetaData& obj)
		{
			std::string log = obj.value;

			const ObjectMetaData* node = obj.parent;
			while(node)
			{
				if(node->parent != nullptr)
				{
					log = node->value + "." + log;
				}

				node = node->parent;
			}

			_error(line, "object '" + log + "' already defined.");
		}

		bool MaterialParser::NoError()
		{
			return m_bNoError;
		}
		ObjectMetaData*	MaterialParser::GetObjectTree()
		{
			return &m_root;
		}
		bool MaterialParser::ParseObjectTree(ObjectMetaData* root)
		{

			if(root->members.size() == 0)
			{
				return true;
			}

			for(auto& v : root->members)
			{
				if(false == ParseObjectTree(&v))
				{
					return false;
				}
			}

			return true;
		}
		bool MaterialParser::_create_object(ObjectMetaData& obj, const std::string& type, const std::string& name, ObjectMetaData* parent)
		{
			for(const auto & v : m_typeInfoList)
			{
				if(_stricmp(v.name.c_str(), type.c_str()) == 0)
				{
					obj.parent = parent;
					obj.line = -1;
					obj.type = type;
					obj.typeinfo = v;
					obj.value = name;


					return true;
				}
			}

			return false;
		}
		void MaterialParser::_init_built_in_type_info()
		{
			TypeInfo t;
			t.name = "__assign__";
			t.value_type = "__string__";
			m_builtInTypeInfoList.push_back(t);

		}
		bool MaterialParser::_validate_member(const TypeInfo& parent, const std::string& type, const std::string& name)
		{
			for(auto v : parent.members)
			{
				if(_stricmp(v.first.c_str(), type.c_str()) == 0)
				{
					if(_stricmp(v.second.c_str(), name.c_str()) == 0)
					{
						return true;
					}
				}
			}

			return false;
		}

		bool MaterialParser::Parse(Lexer* pLexer)
		{
			Token token = pLexer->NextToken();

			while(NoError())
			{
				switch(token.type)
				{
				case Token::token_misc:
					token = _parse_misc();
					break;

				case Token::token_id:
					token = _parse_identifier(m_root);
					break;
				case Token::token_eof:
					return ParseObjectTree(&m_root);
				default:
					_error(token.line, "unexpected token: '" + token.str + "'");
					token = pLexer->NextToken();
					break;
				}
			}

			_error(-1, "====== failed. ======");
			return false;
		}
	}

	namespace material_script
	{
		MaterialParser2::MaterialParser2(BaseParser* parent, std::function<void (const std::string&)> logger) : BaseParser(parent, logger)
		{
		}
		MaterialParser2::~MaterialParser2()
		{

		}
		bool MaterialParser2::Parse(Lexer* lexer)
		{
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
		bool MaterialParser2::ParseIdentifier(Lexer* lexer)
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

				if(pParser->Parse(lexer) == false)
				{
					return false;
				}

				m_members.push_back(pParser);
				return true;
			}
			Error(token.line, "unexpected token: '" + token.str + "'");
			return false;
		}
	}
}

#pragma once

#include "core/MaterialLexer.h"
#include <map>

namespace ld3d
{
	namespace material_script
	{
		struct TypeInfo
		{
			std::string											name;
			std::string											value_type;

			std::vector<std::pair<std::string, std::string>>	members;

			std::vector<std::string>							allowed_value;
		};

		struct MemDef
		{
			TypeInfo											type;
			std::string											name;
			std::vector<std::string>							allowed_value;

		};

		struct ObjectMetaData
		{
			std::string											type;
			std::string											value;
			std::vector<ObjectMetaData>							members;
			TypeInfo											typeinfo;
			ObjectMetaData*										parent;
			int													line;
		};

		class EXPORT_CLASS Parser
		{
		public:

			Parser(std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~Parser(void);

			bool												Parse(const std::string& src, 
																	const std::vector<std::string>& const_list = std::vector<std::string>());

			ObjectMetaData*										GetObjectTree();

		private:

			bool												ParseObjectTree(ObjectMetaData* root);

			void												_reset(const std::string& src);
			void												_error(int line, const std::string& msg);

			Token												_parse_identifier(ObjectMetaData& obj);
			Token												_parse_misc();

			Token												_parse_object(ObjectMetaData& obj);
			Token												_parse_function_call(ObjectMetaData& obj);
			Token												_parse_expr_assign(ObjectMetaData& obj);

			bool												_already_defined(const std::string& value, const ObjectMetaData& scope);

			void												_error_already_defined(int line, const ObjectMetaData& obj);

			const ObjectMetaData*								_find_obj_ref(const std::string& name, const ObjectMetaData& scope);

			bool												NoError();

			bool												_create_object(ObjectMetaData& obj, const std::string& type, const std::string& name, ObjectMetaData* parent);

			void												_init_built_in_type_info();
			bool												_validate_member(const TypeInfo& parent, const std::string& type, const std::string& name);
		private:
			Lexer												m_lexer;
			bool												m_bNoError;
			ObjectMetaData										m_root;

			std::function<void (const std::string&)>			m_logger;

			std::vector<TypeInfo>								m_typeInfoList;
			std::vector<TypeInfo>								m_builtInTypeInfoList;
		};
	}
}

#pragma once

#include "core/MaterialLexer.h"
#include <map>

namespace ld3d
{
	namespace material_script
	{
		struct ClassMetaData
		{
			std::string											value;
			std::vector<ClassMetaData>							members;
		};

		struct ObjectMetaData
		{
			std::string											type;
			std::string											value;
			std::vector<ObjectMetaData>							members;

			ObjectMetaData*										parent;
		};
		class EXPORT_CLASS Parser
		{
		public:
			Parser(void);
			virtual ~Parser(void);

			bool												Parse(const std::string& src);
		private:

			void												_reset(const std::string& src);
			void												_log(int line, const std::string& msg);

			Token												_parse_identifier(ObjectMetaData& obj);
			Token												_parse_misc();

			Token												_parse_object(ObjectMetaData& obj);
			Token												_parse_function_call(ObjectMetaData& obj);
			Token												_parse_expr_assign(ObjectMetaData& obj);

			bool												_already_defined(const std::string& value, const ObjectMetaData& scope);

			void												_log_already_defined(int line, const ObjectMetaData& obj);
		private:
			Lexer												m_lexer;
		};
	}

}
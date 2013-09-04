#pragma once

namespace ld3d
{
	namespace material_script
	{
		class _DLL_CLASS BaseParser
		{
		public:
			BaseParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~BaseParser(void);

			virtual bool										Parse(Lexer* lexer, const boost::filesystem::path& dir = "./")											= 0;

			void												Error(int line, const std::string& msg);
			BaseParserPtr										FindSymbol(const std::string& name, bool curScope);

			BaseParser*											Parent();
			const std::string&									Name();

			bool												str_i_cmp(const std::string& s1, const std::string& s2);

			
			bool												ValidateEnumValue(const std::string& value, char* list[]);
			bool												IsNumber(const std::string& value);
			bool												IsInt(const std::string& value);
			bool												IsVec4(const std::string& value);
			bool												ParseVec4(const std::string& str, math::Vector4& value);
			bool												ParseVec4(Lexer* lexer, std::string& value);
			bool												ParseEnum(const std::string& value, uint32& e, std::pair<std::string, uint32> list[]);
			bool												ParseBool(const std::string& value, bool& ret);
			bool												ParseNumber(const std::string& value, double& ret);
			bool												ParseInt(const std::string& value, int& ret);
			bool												ParseFloat(const std::string& value, float& ret);
		protected:
			std::function<void (const std::string&)>			m_logger;
			BaseParser*											m_parent;
			std::string											m_name;
			std::vector<BaseParserPtr>							m_members;
		};
	}
}

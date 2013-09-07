#include "ogl4graphics_pch.h"
#include "OGL4ShaderCompiler.h"
#include "OGL4Shader.h"
#include "OGL4Convert.h"

#include <regex>

#include <boost/lexical_cast.hpp>

namespace ld3d
{
	OGL4ShaderCompiler::OGL4ShaderCompiler(void)
	{
	}

	OGL4ShaderCompiler::~OGL4ShaderCompiler(void)
	{
	}
	std::string OGL4ShaderCompiler::LoadShaderSource(const boost::filesystem::path& path)
	{
		FILE* file = fopen(path.string().c_str(), "rb");

		if(file == nullptr)
		{
			return "";
		}

		SCOPE_EXIT(fclose(file));

		fseek(file, 0, SEEK_END);
		
		uint64 size = ftell(file);

		fseek(file, (long)0, SEEK_SET);

		char *szCode = new char[size + 1];
		SCOPE_EXIT(delete[] szCode);

		
		fread(szCode, 1, size, file);

		szCode[size] = 0;

		return szCode;
	}
	OGL4ShaderPtr OGL4ShaderCompiler::CreateShaderFromFile(SHADER_TYPE type, const boost::filesystem::path& path)
	{
	
		std::string source = LoadShaderSource(path.string());
		
		
		if(source == "")
		{
			return OGL4ShaderPtr();
		}
		


		std::vector<IncludeInfo> inc_list;
		IncludeInfo inc;
		inc.file = path;
		inc.lines = GetSourceLines(source);

		inc_list.push_back(inc);
		source = ProcessInclude(path.parent_path(), source, inc_list);
		
		inc_list.push_back(inc);
		inc_list.erase(inc_list.begin());


		source = ClearVersionComment(source);

		return CreateShaderFromSource(type, source, inc_list);


	}
	OGL4ShaderPtr OGL4ShaderCompiler::CreateShaderFromSource(SHADER_TYPE type, const std::string& source, const std::vector<IncludeInfo>& inc_list)
	{
		GLenum gltype = OGL4Convert::ShaderTypeToGL(type);
		
		GLuint shader = glCreateShader(gltype);

		const char* szSource = source.c_str();

		glShaderSource(shader, 1, &szSource, 0);

		glCompileShader(shader);

		char szInfo[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, szInfo); 

		PrintShaderLog(szInfo, inc_list);

		GLint ret = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
		if(ret == GL_FALSE)
		{
			glDeleteShader(shader);
			return nullptr;
		}
		
		OGL4ShaderPtr pShader = std::make_shared<OGL4Shader>(type, shader);
		return pShader;
	}
	std::string OGL4ShaderCompiler::ProcessInclude(const boost::filesystem::path& basePath, const std::string& source, std::vector<IncludeInfo>& inc_list)
	{
		std::vector<IncludeInfo> include_list = ExtractIncludeList(source);

		if(include_list.size() == 0)
		{
			return source;
		}

		std::string ret = "";
		for(size_t i = 0; i < include_list.size(); ++i)
		{
			bool included = false;
			for(auto v : inc_list)
			{
				if((basePath / v.file.filename()) == (basePath / include_list[i].file.filename()))
				{
					included = true;
					break;
				}
			}

			if(included)
			{
				continue;
			}
			
			std::string inc_source = LoadShaderSource(basePath / include_list[i].file.filename());
			
			include_list[i].lines = GetSourceLines(inc_source);
			
			ret += ProcessInclude(basePath, inc_source, inc_list) + "\n";
			
			inc_list.push_back(include_list[i]);
		}

		ret += source;

		return ret;
	}
	std::vector<OGL4ShaderCompiler::IncludeInfo> OGL4ShaderCompiler::ExtractIncludeList(const std::string& source)
	{
		std::regex r("#pragma include .*");

		std::string str = source;
		std::regex_iterator<std::string::iterator> rit(str.begin(), str.end(), r);
		std::regex_iterator<std::string::iterator> rend;

		std::vector<std::string> result;

		for(;rit != rend; ++rit)
		{
			result.push_back(rit->str());
		}

		std::vector<IncludeInfo> inc_list;
		for(auto v : result)
		{
			std::regex r("\".*\"");

			std::regex_iterator<std::string::iterator> rit(v.begin(), v.end(), r);
			std::regex_iterator<std::string::iterator> rend;

			if(rit == rend || rit->str().length() <= 2)
			{
				continue;
			}
			IncludeInfo inc;
			inc.file = rit->str().substr(1, rit->str().length() - 2);
			inc.lines = 0;
			
			inc_list.push_back(inc);
		}

		return inc_list;
	}
	std::string OGL4ShaderCompiler::ClearVersionComment(const std::string& source)
	{
		std::regex r("#version .*");

		std::string str = source;
		std::regex_iterator<std::string::iterator> rit(str.begin(), str.end(), r);
		std::regex_iterator<std::string::iterator> rend;

		std::string first = rit->str();

		std::regex rv("#version .*");

		std::string fmt = "";

		std::string result = std::regex_replace(source, rv, fmt);

		return first + result;
	}
	
	void OGL4ShaderCompiler::PrintShaderLog(std::string log, const std::vector<IncludeInfo>& inc_list)
	{
		if(log == "")
		{
			return;
		}
		std::regex r("\n");
		std::sregex_token_iterator first(log.begin(), log.end(), r, -1);
		std::sregex_token_iterator last;
		
		for(auto it = first; it != last; ++it)
		{
			std::string msg = AdjustLog(it->str(), inc_list);

			logger() << msg << "\n";
		}
	}
	int OGL4ShaderCompiler::GetSourceLines(const std::string& src)
	{
		std::regex r("\n");
		std::sregex_token_iterator first(src.begin(), src.end(), r, -1);
		std::sregex_token_iterator last;
		
		int lines = 0;
		for(auto it = first; it != last; ++it)
		{
			++lines;
		}

		return lines + 1;
	}
	std::string OGL4ShaderCompiler::AdjustLog(const std::string& log, const std::vector<IncludeInfo>& inc_list)
	{
		std::regex r("\\([0-9]+\\)");
		std::sregex_iterator first(log.begin(), log.end(), r);
		std::sregex_iterator last;

		std::string s = first->str();

		std::regex rn("[0-9]+");
		std::sregex_iterator rn_first(s.begin(), s.end(), rn);
		std::sregex_iterator rn_last;

		s = rn_first->str();

		int line = strtol(s.c_str(), nullptr, 10);

		std::string result;

		int totals = 0;

		for(size_t i = 0; i < inc_list.size(); ++i)
		{
			if(line <= inc_list[i].lines)
			{
				result = inc_list[i].file.string() + "(" + boost::lexical_cast<std::string>(line) + "):";
				break;
			}
			line -= inc_list[i].lines;
		}

		return result + log.substr(s.length() + 5);
	}
}

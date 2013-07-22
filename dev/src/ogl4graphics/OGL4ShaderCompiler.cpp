#include "ogl4graphics_pch.h"
#include "OGL4ShaderCompiler.h"
#include "OGL4Shader.h"
#include "OGL4Convert.h"

#include <regex>


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
		
		std::vector<boost::filesystem::path> inc_list;
		inc_list.push_back(path.filename());
		source = ProcessInclude(path.parent_path(), source, inc_list);

		source = ClearVersionComment(source);

		return CreateShaderFromSource(type, source, path);


	}
	OGL4ShaderPtr OGL4ShaderCompiler::CreateShaderFromSource(SHADER_TYPE type, const std::string& source, const boost::filesystem::path& file)
	{
		GLenum gltype = OGL4Convert::ShaderTypeToGL(type);
		
		GLuint shader = glCreateShader(gltype);

		const char* szSource = source.c_str();

		glShaderSource(shader, 1, &szSource, 0);

		glCompileShader(shader);

		char szInfo[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, szInfo); 

		PrintShaderLog(szInfo, file);

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
	std::string OGL4ShaderCompiler::ProcessInclude(const boost::filesystem::path& basePath, const std::string& source, std::vector<boost::filesystem::path>& inc_list)
	{
		std::vector<boost::filesystem::path> include_list = ExtractIncludeList(source);

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
				if((basePath / v) == (basePath / include_list[i]))
				{
					included = true;
					break;
				}
			}

			if(included)
			{
				continue;
			}
			inc_list.push_back(include_list[i]);

			std::string inc_source = LoadShaderSource(basePath / include_list[i]);
			ret += ProcessInclude(basePath, inc_source, inc_list);
		}

		ret += source;

		return ret;
	}
	std::vector<boost::filesystem::path> OGL4ShaderCompiler::ExtractIncludeList(const std::string& source)
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

		std::vector<boost::filesystem::path> inc_list;
		for(auto v : result)
		{
			std::regex r("\".*\"");

			std::regex_iterator<std::string::iterator> rit(v.begin(), v.end(), r);
			std::regex_iterator<std::string::iterator> rend;

			if(rit == rend || rit->str().length() <= 2)
			{
				continue;
			}
			std::string inc = rit->str().substr(1, rit->str().length() - 2);
			
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

		return first + "\n" + result;
	}
	
	void OGL4ShaderCompiler::PrintShaderLog(std::string log, const boost::filesystem::path& file)
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
			g_log(file.string() + ":" + it->str() + "\n");
		}
	}
}

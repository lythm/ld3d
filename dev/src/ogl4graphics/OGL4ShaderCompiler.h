#pragma once

#include <boost/filesystem/path.hpp>
namespace ld3d
{
	class OGL4ShaderCompiler
	{
	public:
		OGL4ShaderCompiler(void);
		virtual ~OGL4ShaderCompiler(void);

		static OGL4ShaderPtr								CreateShaderFromFile(SHADER_TYPE type, const boost::filesystem::path& path);
		static OGL4ShaderPtr								CreateShaderFromSource(SHADER_TYPE type, const std::string& source);

	private:
		static std::string									LoadShaderSource(const boost::filesystem::path& path);

		static std::string									ProcessInclude(const boost::filesystem::path& basePath, 
																const std::string& source, 
																std::vector<boost::filesystem::path>& inc_list = std::vector<boost::filesystem::path>());

		static std::vector<boost::filesystem::path>			ExtractIncludeList(const std::string& source);

		static std::string									ClearVersionComment(const std::string& source);

		
	};


}
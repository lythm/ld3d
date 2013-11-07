#pragma once

#include <boost/filesystem/path.hpp>
namespace ld3d
{
	class OGL4ShaderCompiler
	{
		struct IncludeInfo
		{
			IncludeInfo()
			{
				lines = 0;
			}
			boost::filesystem::path							file;
			int												lines;

		};
	public:
		OGL4ShaderCompiler(void);
		virtual ~OGL4ShaderCompiler(void);

		static OGL4ShaderPtr								CreateShaderFromFile(SHADER_TYPE type, const boost::filesystem::path& path, const std::string& entry);
		static OGL4ShaderPtr								CreateShaderFromSource(SHADER_TYPE type, const std::string& source, const std::vector<IncludeInfo>& inc_list, const std::string& entry);

	private:
		static std::string									LoadShaderSource(const boost::filesystem::path& path);

		static std::string									ProcessInclude(const boost::filesystem::path& basePath, 
																const std::string& source, 
																std::vector<IncludeInfo>& inc_list = std::vector<IncludeInfo>());

		static std::vector<IncludeInfo>						ExtractIncludeList(const std::string& source);

		static std::string									ClearVersionComment(const std::string& source);

		static void											PrintShaderLog(std::string log, const std::vector<IncludeInfo>& inc_list);
	
		static int											GetSourceLines(const std::string& src);

		static std::string									AdjustLog(const std::string& log, const std::vector<IncludeInfo>& inc_list);

		static std::string									AdjustEntryPoint(const std::string& src, const std::string& entry);
	};
}

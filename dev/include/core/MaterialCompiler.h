#pragma once
#include <unordered_map>

#include "core/MaterialParser.h"
namespace ld3d
{
	namespace material_script
	{
		class EXPORT_CLASS Compiler
		{
		public:
			Compiler(void);
			virtual ~Compiler(void);

			Material2Ptr											CompileFromFile(Sys_Graphics2Ptr pGraphics, const boost::filesystem::path& strFile);
			Material2Ptr											CompileFromStream(Sys_Graphics2Ptr pGraphics, DataStream* pStream, const boost::filesystem::path& filename = "");
			Material2Ptr											Compile(Sys_Graphics2Ptr pGraphics, const std::string& src, const boost::filesystem::path& filename = "");



		private:
			void													_log(const std::string& msg);
		private:
			boost::filesystem::path									m_file;
		};
	}
}

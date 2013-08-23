#pragma once
#include <unordered_map>

#include "core/MaterialParser.h"
namespace ld3d
{
	namespace material_script
	{
		class _DLL_CLASS Compiler
		{
		public:
			Compiler(void);
			virtual ~Compiler(void);

			MaterialPtr											CompileFromFile(Sys_GraphicsPtr pGraphics, const boost::filesystem::path& strFile);
			MaterialPtr											CompileFromStream(Sys_GraphicsPtr pGraphics, DataStream* pStream, const boost::filesystem::path& filename = "");
			MaterialPtr											Compile(Sys_GraphicsPtr pGraphics, const std::string& src, const boost::filesystem::path& filename = "");



		private:
			void													_log(const std::string& msg);
		private:
			boost::filesystem::path									m_file;
		};
	}
}

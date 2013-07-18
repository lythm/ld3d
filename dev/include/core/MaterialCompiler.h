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

			Material2Ptr											CompileFromFile(const std::string& strFile);
			Material2Ptr											CompileFromStream(DataStream* pStream, const std::string& filename = "");
			Material2Ptr											Compile(const std::string& src, const std::string& filename = "");



		private:
			void													_log(const std::string& msg);

			Material2Ptr											GenerateMaterial();

		private:
			std::string												m_file;
			MaterialParser											m_parser;
		};
	}
}
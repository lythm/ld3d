#include "core_pch.h"
#include "..\..\include\core\MaterialCompiler.h"
#include "core_utils.h"
#include "core/DataStream_File.h"


namespace ld3d
{
	namespace material_script
	{
		Compiler::Compiler(void) : m_parser(std::bind(&Compiler::_log, this, std::placeholders::_1))
		{
		}


		Compiler::~Compiler(void)
		{
		}
		
		Material2Ptr Compiler::CompileFromStream(DataStream* pStream, const std::string& filename)
		{
			uint64 size = pStream->Size();
			char* szSrc = new char[size + 1];
			szSrc[size] = 0;
			SCOPE_EXIT(delete szSrc);

			pStream->Read(szSrc, size);

			return Compile(szSrc, filename);
		}
		Material2Ptr Compiler::CompileFromFile(const std::string& strFile)
		{
			DataStream_File file;
			if(false == file.OpenStream(strFile.c_str()))
			{
				return Material2Ptr();
			}

			return CompileFromStream(&file, strFile);
		}
		Material2Ptr Compiler::Compile(const std::string& src, const std::string& filename)
		{
			m_file = filename;

			std::vector<std::string> const_list;
			const_list.push_back("wireframe");


			m_parser.Parse(src, const_list);
			return GenerateMaterial();
		}
		void Compiler::_log(const std::string& msg)
		{
			log(m_file + msg);
		}
		Material2Ptr Compiler::GenerateMaterial()
		{
			return Material2Ptr();
		}
	}
}

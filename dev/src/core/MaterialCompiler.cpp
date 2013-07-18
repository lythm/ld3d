#include "core_pch.h"
#include "..\..\include\core\MaterialCompiler.h"
#include "core_utils.h"
#include "core/DataStream_File.h"


namespace ld3d
{
	namespace material_script
	{
		Compiler::Compiler(void)
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

			Lexer lexer(src);
			

			MaterialParser2 parser(nullptr, std::bind(&Compiler::_log, this, std::placeholders::_1));

			if(false == parser.Parse(&lexer))
			{
				return Material2Ptr();
			}



		//	pParser->Parse();

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

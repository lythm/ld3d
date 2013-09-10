#include "core_pch.h"
#include "core/MaterialCompiler.h"
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
		
		MaterialPtr Compiler::CompileFromStream(Sys_GraphicsPtr pGraphics, DataStream* pStream, const boost::filesystem::path& filename)
		{
			uint64 size = pStream->Size();
			char* szSrc = new char[size + 1];
			szSrc[size] = 0;
			SCOPE_EXIT(delete szSrc);

			pStream->Read(szSrc, size);

			return Compile(pGraphics, szSrc, filename);
		}
		MaterialPtr Compiler::CompileFromFile(Sys_GraphicsPtr pGraphics, const boost::filesystem::path& strFile)
		{
			DataStream_File file;
			if(false == file.OpenStream(strFile.string().c_str()))
			{
				return MaterialPtr();
			}

			return CompileFromStream(pGraphics, &file, strFile);
		}
		MaterialPtr Compiler::Compile(Sys_GraphicsPtr pGraphics, const std::string& src, const boost::filesystem::path& filename)
		{
			m_file = filename;

			logger() << "compiling material(" << m_file << "): \n";
			
			Lexer lexer(src);
			
			MaterialParser parser(nullptr, logger());

			if(false == parser.Parse(&lexer, m_file == "" ? "./" : m_file.parent_path()))
			{
				logger() << "failed. \n";
				return MaterialPtr();
			}
			logger() << "ok. \n";
			return parser.CreateObject(pGraphics);
		}
		
	}
}

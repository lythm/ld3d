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
			if(false == file.OpenStream(strFile.c_str()))
			{
				return MaterialPtr();
			}

			return CompileFromStream(pGraphics, &file, strFile);
		}
		MaterialPtr Compiler::Compile(Sys_GraphicsPtr pGraphics, const std::string& src, const boost::filesystem::path& filename)
		{
			m_file = filename;

			Lexer lexer(src);
			
			MaterialParser parser(nullptr, std::bind(&Compiler::_log, this, std::placeholders::_1));

			if(false == parser.Parse(&lexer, m_file == "" ? "./" : m_file.parent_path()))
			{
				return MaterialPtr();
			}
			
			return parser.CreateObject(pGraphics);
		}
		void Compiler::_log(const std::string& msg)
		{
			log(m_file.string() + msg);
		}
	}
}

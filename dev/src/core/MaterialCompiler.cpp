#include "core_pch.h"
#include "..\..\include\core\MaterialCompiler.h"
#include "core_utils.h"
#include "core/DataStream_File.h"

namespace ld3d
{
	static std::string sampler_variable_list[] = 
	{
		"address_u",
		"address_v",
		"address_w",
	};

	static std::string render_state_variable_list[]=
	{
		"cullmode",
		"fillmode",

	};

	static std::string function_list[] = 
	{
		"setvertexshader",
		"setpixelshader",
		"setgeometryshader",
		"setrenderstate",
		"bindsampler",
	};

	MaterialCompiler::MaterialCompiler(void)
	{
		m_curPos = 0;
	}


	MaterialCompiler::~MaterialCompiler(void)
	{
		Clear();
	}
	void MaterialCompiler::InitParser()
	{
		m_parser["samplerstate"] = std::bind(&MaterialCompiler::ParseSampler, this, std::placeholders::_1);
		m_parser["renderstate"] = std::bind(&MaterialCompiler::ParseRenderState, this, std::placeholders::_1);
		m_parser["technique"] = std::bind(&MaterialCompiler::ParseTech, this, std::placeholders::_1);
		m_parser["pass"] = std::bind(&MaterialCompiler::ParseTech, this, std::placeholders::_1);
	}

	Material2Ptr MaterialCompiler::CompileFromStream(DataStream* pStream, const std::string& filename)
	{
		uint64 size = pStream->Size();
		char* szSrc = new char[size + 1];
		szSrc[size] = 0;
		SCOPE_EXIT(delete szSrc);

		pStream->Read(szSrc, size);
		
		return Compile(szSrc, filename);
	}
	Material2Ptr MaterialCompiler::CompileFromFile(const std::string& strFile)
	{
		
		DataStream_File file;
		if(false == file.OpenStream(strFile.c_str()))
		{
			return Material2Ptr();
		}
		
		return CompileFromStream(&file, strFile);
	}
	Material2Ptr MaterialCompiler::Compile(const std::string& src, const std::string& filename)
	{
		Clear();

		m_lexer.Reset(src);

		InitParser();
		m_file = filename;
		m_src = src;

		ConstructLineInfo();


		MaterialLexer::MaterialToken token = m_lexer.NextToken();

		while(true)
		{
			switch(token)
			{
			case MaterialLexer::token_semi:
				m_lexer.NextToken();
				break;
			default:
				break;
			}
		}







		int pos = 0;
		while(pos >= 0)
		{
			pos = ParseObject(pos);
			if(pos == ret_no_obj_left)
			{
				break;
			}
			if(pos < 0)
			{
				return Material2Ptr();
			}
		}

		return GenerateMaterial();
	}
	bool MaterialCompiler::IsComment(int offset)
	{
		int pos = offset;
		
		for(int i = 0; i < 2; ++i, ++pos)
		{
			if(pos >= m_src.length())
			{
				return false;
			}
						
			if(Char(pos) != '/')
			{
				return false;
			}
		}
		
		return true;
	}
	bool MaterialCompiler::IsToken(const std::string& token, int offset)
	{
		int pos = offset;
		
		for(int i = 0; i < token.length(); ++i, ++pos)
		{
			if(pos >= m_src.length())
			{
				return false;
			}

			
			if(tolower(token[i]) != tolower(Char(pos)))
			{
				return false;
			}
		}
		if((pos) == m_src.length())
		{
			return true;
		}

		if(isalnum(Char(pos)) == 0 && Char(pos) != '_')
		{
			return true;
		}

		return true;
	}
	int MaterialCompiler::SkipWhite(int offset)
	{
		int pos = offset;
		while(pos < m_src.length() &&(Char(pos) == ' ' || Char(pos) == '\n' || Char(pos) == '\r' || Char(pos) ==  '\t'))
		{
			
			pos++;
		}
		if(pos == m_src.length())
		{
			return ret_eof;
		}
		return pos;
	}
	int	MaterialCompiler::DiscardLine(int offset)
	{
		int line, col;
		bool ret = PosToLineCol(offset, line, col);
		if(ret == false)
		{
			return ret_failed;
		}
		
		if(line == m_lines.size() - 1)
		{
			return ret_eof;
		}

		return m_lines[line + 1].start;
	}
	int	MaterialCompiler::ExpectNewLine(int offset)
	{
		int pos = offset;
		while(Char(pos) == ' ' || Char(pos) ==  '\t')
		{
			if(pos == m_src.length())
			{
				return ret_eof;
			}
			pos++;
		}

		if(pos >= m_src.length())
		{
			return ret_eof;
		}

		if(Char(pos) == '\n')
		{
			return pos + 1;
		}

		if(Char(pos) == '\r')
		{
			return pos + 2;
		}

		return ret_failed;
	}
	int MaterialCompiler::ExpectLeftParentheses(int offset)
	{
		return ExpectTokenAs(offset, "(");
	}
	int	MaterialCompiler::ExpectRightParentheses(int offset)
	{
		return ExpectTokenAs(offset, ")");
	}
	int	MaterialCompiler::ExpectTokenAs(int offset, const std::string& token)
	{
		std::string t;
		int pos = ExpectToken(offset, t);
		if(pos < 0)
		{
			return pos;
		}
		if(IsToken(t, token) == false)
		{
			return ret_failed;
		}
		
		return pos;
	}
	int	MaterialCompiler::ExpectLeftBrace(int offset)
	{
		return ExpectTokenAs(offset, "{");
	}
	int MaterialCompiler::ExpectRightBrace(int offset)
	{
		return ExpectTokenAs(offset, "}");
	}
	bool MaterialCompiler::ConstructLineInfo()
	{
		int start = 0;
		int len = 0;
		for(int i = 0; i < m_src.length(); ++i)
		{
			if(Char(i) == '\n' || Char(i) == '\r')
			{
				LineInfo info;
				info.start = start;
				info.len = len;

				m_lines.push_back(info);

				if(Char(i) == '\r')
				{
					++i;
				}

				start = i + 1;
				len = 0;
				continue;
			}

			++len;
		}

		if(len != 0)
		{
			LineInfo info;
			info.start = start;
			info.len = len;

			m_lines.push_back(info);
		}
		return true;
	}
	void MaterialCompiler::Clear()
	{
		m_src = "";
		m_lines.clear();
		m_curPos = 0;
		m_file = "";
		m_parser.clear();
	}
	bool MaterialCompiler::PosToLineCol(int pos, int& line, int& col)
	{
		if(pos == -1)
		{
			return false;
		}

		for(size_t i = 0; i < m_lines.size(); ++i)
		{
			if(pos >= m_lines[i].start && (pos - m_lines[i].start) <= m_lines[i].len)
			{
				line = i;
				col = pos - m_lines[i].start;
				return true;
			}
		}

		return false;
	}
	std::string MaterialCompiler::LogPrefix(int pos)
	{
		int line , col;
		line = col = -1;
		PosToLineCol(pos, line, col);
		if(m_file.length() == 0)
		{
			return "line[" + std::to_string(line + 1) + "]: ";
		}
		
		return m_file + "[" + std::to_string(line + 1) + "]["+std::to_string(col + 1)+"]: ";
	}
	
	std::string	MaterialCompiler::LogPrefix()
	{
		return LogPrefix(m_curPos);
	}
	char MaterialCompiler::Char(int offset)
	{
		m_curPos = offset;
		return m_src[offset];
	}
	int	MaterialCompiler::ExpectToken(int offset, std::string& token)
	{
		// skip white and comment
		int pos = offset;
		while(true)
		{
			pos = SkipWhite(pos);
			if(pos == ret_eof)
			{
				return ret_eof;
			}

			if(IsComment(pos) == false)
			{
				break;
			}

			pos = DiscardLine(pos);
			if(pos < 0)
			{
				return pos;
			}
		}
		
		// brace
		if(Char(pos) == '{' || Char(pos) == '}')
		{
			token = Char(pos);
			return pos + 1;
		}

		if(isalpha(Char(pos)) == 0 && Char(pos) != '_')
		{
			token += Char(pos);
			return ret_failed;
		}

		while((isalnum(Char(pos)) != 0 || Char(pos) == '_') && pos < m_src.length())
		{
			token += Char(pos);
			pos++;
		}
		
		if(token.length() == 0)
		{
			return ret_failed;
		}

		return pos;
	}
	void MaterialCompiler::Print(const std::string& info)
	{
		log(LogPrefix() + info);
	}
	int MaterialCompiler::ParseObject(int offset)
	{
		std::string token = "";
		int pos = ExpectToken(offset, token);
		if(pos == ret_eof)
		{
			return ret_no_obj_left;
		}
		
		if(pos < 0)
		{
			Print("Invalid token: " + token);
			return pos;
		}

		auto func =  m_parser[ToLower(token)];

		if(func == nullptr)
		{
			Print("Unknown token: " + token);
			return ret_failed;
		}
		
		return func(pos);
	}
	int MaterialCompiler::ParseSampler(int offset)
	{
		std::string id = "";
		int pos = ExpectToken(offset, id);
		if(pos == ret_eof)
		{
			Print("Sampler name expected, not found.");
			return ret_eof;
		}
		if(pos == ret_failed)
		{
			Print("Invalid sampler name: " + id);
			return ret_failed;
		}

		if(HasDefined(id))
		{
			Print(id + " already defined.");
			return ret_failed;
		}

		pos = ExpectLeftBrace(pos);
		if(pos < 0)
		{
			Print("'{' expected, not found.");
			return pos;
		}
		// parse members


		pos = ExpectRightBrace(pos);
		if(pos < 0)
		{
			Print("'}' expected, not found.");
			return pos;
		}

		SamplerInfo info;
		info.m_name = id;

		m_samplers.push_back(info);
		return pos;
	}
	int MaterialCompiler::ParseRenderState(int offset)
	{
		std::string id = "";
		int pos = ExpectToken(offset, id);
		if(pos == ret_eof)
		{
			Print("RenderState name expected, not found.");
			return ret_eof;
		}
		if(pos == ret_failed)
		{
			Print("Invalid RenderState name: " + id);
			return ret_failed;
		}

		if(HasDefined(id))
		{
			Print(id + " already defined.");
			return ret_failed;
		}

		pos = ExpectLeftBrace(pos);
		if(pos < 0)
		{
			Print("'{' expected, not found.");
			return pos;
		}
		// parse members


		pos = ExpectRightBrace(pos);
		if(pos < 0)
		{
			Print("'}' expected, not found.");
			return pos;
		}

		RenderStateInfo info;
		info.m_name = id;

		m_renderstates.push_back(info);
		return pos;
	}
	int MaterialCompiler::ParseTech(int offset)
	{
		TechniqueInfo info;
		
		std::string id = "";
		int pos = ExpectToken(offset, id);
		if(pos == ret_eof)
		{
			Print("Technique name expected, not found.");
			return ret_eof;
		}
		if(pos == ret_failed)
		{
			Print("Invalid Technique name: " + id);
			return ret_failed;
		}

		if(HasDefined(id))
		{
			Print(id + " already defined.");
			return ret_failed;
		}

		info.m_name = id;


		pos = ExpectLeftBrace(pos);
		if(pos < 0)
		{
			Print("'{' expected, not found.");
			return pos;
		}
		// parse members

		while(true)
		{
			std::string token = "";
			pos = ExpectToken(pos, token);
			if(pos < 0)
			{
				Print("'pass or }' expected, not found.");
				return pos;
			}
		
			if(IsToken(token, "pass") == false)
			{
				pos -= token.length();
				break;
			}
			PassInfo pass;
			pos = ParsePass(pos, pass);
			if(pos < 0)
			{
				return pos;
			}

			info.m_passes.push_back(pass);
		}

		pos = ExpectRightBrace(pos);
		if(pos < 0)
		{
			Print("'}' expected, not found.");
			return pos;
		}

		

		m_techs.push_back(info);
		return pos;
	}
	std::string MaterialCompiler::ToLower(const std::string& str)
	{
		std::string ret;
		for(size_t i = 0; i < str.length(); ++i)
		{
			ret += isalpha(str[i]) ? towlower(str[i]) : str[i];
		}
		return ret;
	}
	int MaterialCompiler::ParsePass(int offset, PassInfo& info)
	{
		std::string id = "";
		int pos = ExpectToken(offset, id);
		if(pos == ret_eof)
		{
			Print("Pass name expected, not found.");
			return ret_eof;
		}
		if(pos == ret_failed)
		{
			Print("Invalid Pass name: " + id);
			return ret_failed;
		}

		if(HasDefined(id))
		{
			Print(id + " already defined.");
			return ret_failed;
		}

		pos = ExpectLeftBrace(pos);
		if(pos < 0)
		{
			Print("'{' expected, not found.");
			return pos;
		}
		// parse members


		pos = ExpectRightBrace(pos);
		if(pos < 0)
		{
			Print("'}' expected, not found.");
			return pos;
		}

		info.m_name = id;
		return pos;
	}
	bool MaterialCompiler::HasDefined(const std::string& name)
	{
		for(size_t i = 0; i < m_samplers.size(); ++i)
		{
			if(m_samplers[i].m_name == name)
			{
				return true;
			}
		}

		for(size_t i = 0; i < m_renderstates.size(); ++i)
		{
			if(m_renderstates[i].m_name == name)
			{
				return true;
			}
		}

		for(size_t i = 0; i < m_techs.size(); ++i)
		{
			if(m_techs[i].m_name == name)
			{
				return true;
			}
		}

		return false;
	}

	bool MaterialCompiler::IsToken(const std::string& token, const std::string& expecting)
	{
		return ToLower(token) == ToLower(expecting);
	}
	Material2Ptr MaterialCompiler::GenerateMaterial()
	{
		return Material2Ptr();
	}
}


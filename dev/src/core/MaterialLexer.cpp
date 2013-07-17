#include "core_pch.h"
#include "..\..\include\core\MaterialLexer.h"

namespace ld3d
{
	MaterialLexer::MaterialLexer(std::string src)
	{
		Reset(src);
	}


	MaterialLexer::~MaterialLexer(void)
	{
	}
	void MaterialLexer::Reset()
	{
		Reset(m_src);
	}
	void MaterialLexer::Reset(const std::string& src)
	{
		m_src					= src;

		m_curPos				= 0;

		
		m_curToken				= token_eof;
		m_curTokenStr			= "";
		m_curTokenNum			= 0;
		
		_reset_line_info();

	}
	MaterialLexer::MaterialToken MaterialLexer::_get_token()
	{
		int ch = ' ';
		m_curTokenStr = "";
		m_curTokenNum = 0;

		while(isspace(ch))
		{
			ch = _get_char();
		}


		if(ch == ';')
		{
			m_curTokenStr = ';';
			m_curToken = token_semi;
			return m_curToken;
		}

		if(ch == ',')
		{
			m_curTokenStr = ',';
			m_curToken = token_comma;
			return m_curToken;
		}

		if(ch == '+')
		{
			m_curTokenStr = '+';
			m_curToken = token_add;
			return m_curToken;
		}

		if(ch == '-')
		{
			m_curTokenStr = '-';
			m_curToken = token_sub;
			return m_curToken;
		}


		if(ch == '{')
		{
			m_curTokenStr = '{';
			m_curToken = token_lbrace;
			return m_curToken;
		}
		if(ch == '}')
		{
			m_curTokenStr = '}';
			m_curToken = token_rbrace;
			return m_curToken;
		}

		if(ch == '(')
		{
			m_curTokenStr = '(';
			m_curToken = token_lparentheses;
			return m_curToken;
		}
		if(ch == ')')
		{
			m_curTokenStr = ')';
			m_curToken = token_rparentheses;
			return m_curToken;
		}

		if(isalpha(ch))
		{
			m_curTokenStr = ch;

			while(isalnum(ch = _get_char()))
			{
				m_curTokenStr += ch;
			}

			m_curToken = token_id;
			return m_curToken;
		}

		if(isdigit(ch))
		{
			bool dotted = false;
			
			do
			{
				m_curTokenStr += ch;
				if(ch == ',')
				{
					dotted = true;
				}

				ch = _get_char();
			}while(dotted ? isdigit(ch) : (isdigit(ch) || ch == '.'));


			m_curToken = token_number;
			m_curTokenNum = strtod(m_curTokenStr.c_str(), 0);
			return m_curToken;
		}

		if(ch == '#')
		{
			do
			{
				ch = _get_char();
			}while(ch != end_of_input && ch != '\n' && ch != '\r');

			if(ch != end_of_input)
			{
				return _get_token();
			}
		}

		if(ch == end_of_input)
		{
			m_curToken = token_eof;
			return m_curToken;
		}

		m_curToken = token_unknown;
		m_curTokenStr = ch;
		return m_curToken;
	}
	MaterialLexer::MaterialToken MaterialLexer::NextToken()
	{
		return _get_token();
	}
	MaterialLexer::MaterialToken MaterialLexer::CurToken()
	{
		return m_curToken;
	}
	std::string	MaterialLexer::CurTokenString()
	{
		return m_curTokenStr;
	}
	
	int MaterialLexer::_get_char()
	{
		return m_src[m_curPos++];
	}
	double MaterialLexer::CurTokenNum()
	{
		return m_curTokenNum;
	}
	void MaterialLexer::_reset_line_info()
	{
		int start = 0;
		int len = 0;
		for(int i = 0; i < m_src.length(); ++i)
		{
			if(m_src[i] == '\n' || m_src[i] == '\r')
			{
				LineInfo info;
				info.start = start;
				info.len = len;

				m_lines.push_back(info);

				if(m_src[i] == '\r')
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
	}
	bool MaterialLexer::_pos_2_line_col(int pos, int& line, int& col)
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
	int MaterialLexer::CurLine()
	{
		int line = -1;
		int col = -1;
		_pos_2_line_col(m_curPos, line, col);

		return line;
	}
	int	MaterialLexer::CurCol()
	{
		int line = -1;
		int col = -1;
		_pos_2_line_col(m_curPos, line, col);
		return col;
	}
}

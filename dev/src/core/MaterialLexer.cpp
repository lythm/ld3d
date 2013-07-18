#include "core_pch.h"
#include "..\..\include\core\MaterialLexer.h"

namespace ld3d
{
	namespace material_script
	{
		Lexer::Lexer(std::string src)
		{
			Reset(src);
		}


		Lexer::~Lexer(void)
		{
		}
		void Lexer::Reset()
		{
			Reset(m_src);
		}
		void Lexer::Reset(const std::string& src)
		{
			m_src					= src;

			m_curPos				= 0;
			m_lastChar				= ' ';
			_reset_line_info();

		}
		Token Lexer::_get_token()
		{
			m_curToken.str = "";
			m_curToken.num = 0;

			while(isspace(m_lastChar))
			{
				m_lastChar = _get_char();
			}

			m_curToken.line = _current_line();


			if(m_lastChar == '\"')
			{
				
				while((m_lastChar = _get_char() )!= '\"')
				{
					m_curToken.str += m_lastChar;
				}
				m_lastChar = _get_char();
				m_curToken.type = Token::token_string;
				return m_curToken;
			}

			if(isalpha(m_lastChar))
			{
				m_curToken.str = m_lastChar;

				while(isalnum(m_lastChar = _get_char()))
				{
					m_curToken.str += m_lastChar;
				}

				m_curToken.type = Token::token_id;
				return m_curToken;
			}

			if(isdigit(m_lastChar))
			{
				bool dotted = false;

				do
				{
					m_curToken.str += m_lastChar;
					if(m_lastChar == ',')
					{
						dotted = true;
					}

					m_lastChar = _get_char();
				}while(dotted ? isdigit(m_lastChar) : (isdigit(m_lastChar) || m_lastChar == '.'));


				m_curToken.type = Token::token_number;
				m_curToken.num = strtod(m_curToken.str.c_str(), 0);

				return m_curToken;
			}

			if(m_lastChar == '#')
			{
				do
				{
					m_lastChar = _get_char();
				}while(m_lastChar != end_of_input && m_lastChar != '\n' && m_lastChar != '\r');

				if(m_lastChar != end_of_input)
				{
					return _get_token();
				}
			}

			if(m_lastChar == end_of_input)
			{
				m_curToken.type = Token::token_eof;
				m_curToken.str = "eof";
				return m_curToken;
			}

			m_curToken.type = Token::token_misc;
			m_curToken.str = m_lastChar;
			m_lastChar = _get_char();
			return m_curToken;
		}
		Token Lexer::NextToken()
		{
			return _get_token();
		}
		Token Lexer::CurToken()
		{
			return m_curToken;
		}
		

		int Lexer::_get_char()
		{
			return m_src[m_curPos++];
		}
		
		void Lexer::_reset_line_info()
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
		int Lexer::_pos_2_line(int pos)
		{
			if(pos == -1)
			{
				return -1;
			}

			if(pos >= m_src.length())
			{
				return m_lines.size() - 1;
			}

			for(size_t i = 0; i < m_lines.size(); ++i)
			{
				if(pos >= m_lines[i].start && (pos - m_lines[i].start) <= m_lines[i].len)
				{
					return i;
				}
			}

			return -1;
		}
		int Lexer::_current_line()
		{
			return _pos_2_line(m_curPos - 1);
		}
		Token Lexer::SkipToken(Token tok)
		{
			Token token = CurToken();

			while(token.str == tok.str && token.type == tok.type)
			{
				token = NextToken();
			}
			return token;
		}
	}
}

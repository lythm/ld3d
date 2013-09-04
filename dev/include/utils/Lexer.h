#pragma once

#include <vector>
#include <string>

namespace ld3d
{
	struct Token
	{
		enum TokenType
		{
			token_id,
			token_number,
			token_string,
			token_eof,

			token_misc,
		};

		TokenType								type;
		std::string								str;
		double									num;

		int										line;
	};
	class Lexer
	{
		struct LineInfo
		{
			int									start;
			int									len;
		};
	public:

		enum
		{
			end_of_input = 0,
		};

		Lexer(std::string src = "");
		virtual ~Lexer(void);

		void										Reset();
		void										Reset(const std::string& src);

		Token										NextToken();

		Token										CurToken();

		Token										SkipToken(Token tok);
	private:
		Token										_get_token();
		int											_get_char();

		void										_reset_line_info();
		int 										_pos_2_line(int pos);

		int											_current_line();
	private:
		std::string									m_src;
		int											m_curPos;
		Token										m_curToken;
		std::vector<LineInfo>						m_lines;
		int											m_lastChar;
	};

}
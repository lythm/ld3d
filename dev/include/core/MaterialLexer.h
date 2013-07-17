#pragma once

namespace ld3d
{
	class MaterialLexer
	{
		struct LineInfo
		{
			int					start;
			int					len;
		};
	public:

		enum
		{
			end_of_input = 0,
		};

		enum MaterialToken
		{
			token_id,
			token_number,
			token_string,
			token_eof,
			token_lbrace,
			token_rbrace,
			token_lparentheses,
			token_rparentheses,
			token_sub,
			token_add,
			token_semi,
			token_comma,

			token_positive = token_add,
			token_negtive = token_sub,

			token_unknown,
		};

		MaterialLexer(std::string src = "");
		virtual ~MaterialLexer(void);

		void										Reset();
		void										Reset(const std::string& src);

		MaterialToken								NextToken();

		MaterialToken								CurToken();
		std::string									CurTokenString();
		double										CurTokenNum();

		int											CurLine();
		int											CurCol();
	private:
		MaterialToken								_get_token();
		int											_get_char();

		void										_reset_line_info();
		bool										_pos_2_line_col(int pos, int& line, int& col);
	private:
		std::string									m_src;

		int											m_curPos;

		MaterialToken								m_curToken;
		std::string									m_curTokenStr;
		double										m_curTokenNum;

		std::vector<LineInfo>						m_lines;
	};
}

#pragma once
#include <unordered_map>
#include "core/MaterialLexer.h"

namespace ld3d
{
	class EXPORT_CLASS MaterialCompiler
	{
		struct VariableInfo
		{
			std::string						m_name;
			std::string						m_value;
		};
		struct FunctionInfo
		{
			std::string						m_name;
			std::vector<std::string>		m_params;
		};
		struct SamplerInfo
		{
			std::string						m_name;
		};
		struct RenderStateInfo
		{
			std::string						m_name;
		};
		struct PassInfo
		{
			std::string						m_name;
			int								m_renderStateIndex;
			std::string						m_vs;
			std::string						m_gs;
			std::string						m_ps;
		};
		struct TechniqueInfo
		{
			std::string						m_name;
			std::vector<PassInfo>			m_passes;
		};
		enum result
		{
			ret_ok							= -1,
			ret_failed						= -2,
			ret_eof							= -3,
			ret_no_obj_left					= -4,
			
		};
		struct LineInfo
		{
			int					start;
			int					len;
		};
	public:
		MaterialCompiler(void);
		virtual ~MaterialCompiler(void);

		Material2Ptr											CompileFromFile(const std::string& strFile);
		Material2Ptr											CompileFromStream(DataStream* pStream, const std::string& filename = "");
		Material2Ptr											Compile(const std::string& src, const std::string& filename = "");

	
		void													Clear();
	private:
		
		
		bool													IsToken(const std::string& token, int offset);
		bool													IsComment(int offset);

		
		int														SkipWhite(int offset);
		int														ExpectLeftBrace(int offset);
		int														ExpectRightBrace(int offset);
		int														ExpectLeftParentheses(int offset);
		int														ExpectRightParentheses(int offset);

		int														DiscardLine(int offset);
		int														ExpectToken(int offset, std::string& token);
		int														ExpectTokenAs(int offset, const std::string& token);
		int														ExpectNewLine(int offset);
		bool													ConstructLineInfo();

		bool													PosToLineCol(int pos, int& line, int& col);

		std::string												LogPrefix(int pos);
		std::string												LogPrefix();

		void													Print(const std::string& info);

		char													Char(int offset);

		int 													ParseObject(int offset);

		void													InitParser();

		int														ParseSampler(int offset);
		int														ParseRenderState(int offset);
		int														ParseTech(int offset);
		int														ParsePass(int offset, PassInfo& info);

		std::string												ToLower(const std::string& str);

		bool													HasDefined(const std::string& name);

		bool													IsToken(const std::string& token, const std::string& expecting);

		Material2Ptr											GenerateMaterial();
	private:

		std::unordered_map<std::string, 
			std::function<int (int offset)>>					m_parser;

		std::string												m_src;
		std::vector<LineInfo>									m_lines;
		std::string												m_file;
		int														m_curPos;

		std::vector<SamplerInfo>								m_samplers;
		std::vector<RenderStateInfo>							m_renderstates;
		std::vector<TechniqueInfo>								m_techs;

		MaterialLexer											m_lexer;
	};
}
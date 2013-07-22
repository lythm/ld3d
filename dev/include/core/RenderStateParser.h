#pragma once

#include "core/MaterialBaseParser.h"

namespace ld3d
{
	namespace material_script
	{
		class RenderStateParser  : public BaseParser
		{
		public:
			RenderStateParser(BaseParser* parent, std::function<void (const std::string&)> logger = std::function<void (const std::string&)>());
			virtual ~RenderStateParser(void);

			bool												Parse(Lexer* lexer);

			RenderState2Ptr										CreateObject(Sys_Graphics2Ptr pGraphics);
		private:
			bool												SetState(int line, const std::string& name, const std::string& value);
			bool												ParseState(Lexer* lexer);



		private:

			math::Vector4										_BlendFactor;
			bool												_BlendEnable;
			RS_BLEND_OP											_BlendAlphaOP;
			RS_BLEND_OP											_BlendRGBOP;
			RS_BLEND											_BlendSrcRGB;
			RS_BLEND											_BlendDstRGB;
			RS_BLEND											_BlendSrcAlpha;
			RS_BLEND											_BlendDstAlpha;
			RS_COLOR_WRITE										_ColorWrite;
			RS_FILL_MODE										_FillMode;
			RS_CULL_MODE										_CullMode;
			bool												_FrontFaceCounterClockWise;
			bool												_DepthClipEnable;
			bool												_DepthEnable;
			RS_DEPTH_WRITE										_DepthWriteMask;
			RS_COMPARISON_FUNC									_DepthFunc;
			bool												_StencilEnable;
			RS_STENCIL_OP										_FrontFaceStencilFailOP;
			RS_STENCIL_OP										_FrontFaceStencilDepthFailOP;
			RS_STENCIL_OP										_FrontFaceStencilPassOP;
			RS_COMPARISON_FUNC									_FrontFaceStencilFunc;

			RS_STENCIL_OP										_BackFaceStencilFailOP;
			RS_STENCIL_OP										_BackFaceStencilDepthFailOP;
			RS_STENCIL_OP										_BackFaceStencilPassOP;
			RS_COMPARISON_FUNC									_BackFaceStencilFunc;
			
			int													_FrontFaceStencilWriteMask;
			int													_FrontFaceStencilReadMask;
			int													_BackFaceStencilWriteMask;
			int													_BackFaceStencilReadMask;

			int													_FrontFaceStencilRef;
			int													_BackFaceStencilRef;
		};


	}
}
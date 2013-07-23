#pragma once

#include "core/RenderTexture.h"

namespace ld3d
{
	class OGL4RenderTexture : public RenderTexture
	{
	public:
		OGL4RenderTexture(void);
		virtual ~OGL4RenderTexture(void);


		bool														Create();
		void														Release();
		
		int															GetTextureCount();
		void														AddTexture(TexturePtr pTex);

		TexturePtr													GetTexture(int index);

		void														SetDepthStencilBuffer(DepthStencilBufferPtr pDS);
		DepthStencilBufferPtr										GetDepthStencilBuffer();


		GLuint														GetFBO();
	private:
		std::vector<TexturePtr>									m_texs;
		DepthStencilBufferPtr										m_pDS;

		GLuint														m_fbo;
	};
}

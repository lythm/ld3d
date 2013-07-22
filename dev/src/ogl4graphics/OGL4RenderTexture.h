#pragma once

#include "core/RenderTexture.h"

namespace ld3d
{
	class OGL4RenderTexture : public RenderTexture2
	{
	public:
		OGL4RenderTexture(void);
		virtual ~OGL4RenderTexture(void);


		bool														Create();
		void														Release();
		
		int															GetTextureCount();
		void														AddTexture(Texture2Ptr pTex);

		Texture2Ptr													GetTexture(int index);

		void														SetDepthStencilBuffer(DepthStencilBufferPtr pDS);
		DepthStencilBufferPtr										GetDepthStencilBuffer();


		GLuint														GetFBO();
	private:
		std::vector<Texture2Ptr>									m_texs;
		DepthStencilBufferPtr										m_pDS;

		GLuint														m_fbo;
	};
}

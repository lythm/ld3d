#include "ogl4graphics_pch.h"
#include "OGL4RenderTexture.h"
#include "OGL4Texture.h"
#include "OGL4DepthStencilBuffer.h"

namespace ld3d
{
	OGL4RenderTexture::OGL4RenderTexture(void)
	{
		m_fbo = 0;
	}


	OGL4RenderTexture::~OGL4RenderTexture(void)
	{
	}
	bool OGL4RenderTexture::Create()
	{
		glGenFramebuffers(1, &m_fbo);
		return true;
	}
	void OGL4RenderTexture::Release()
	{
		glDeleteFramebuffers(1, &m_fbo);
		m_fbo = 0;
		m_texs.clear();
	}
		
	int	OGL4RenderTexture::GetTextureCount()
	{
		return (int)m_texs.size();
	}
	void OGL4RenderTexture::AddTexture(Texture2Ptr pTex)
	{
		if(pTex == nullptr)
		{
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		
		OGL4Texture* pGLTex = (OGL4Texture*)pTex.get();
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_texs.size(), pGLTex->GetTextureObject(), 0);

		m_texs.push_back(pTex);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Texture2Ptr OGL4RenderTexture::GetTexture(int index)
	{
		return m_texs[index];
	}
	void OGL4RenderTexture::SetDepthStencilBuffer(DepthStencilBufferPtr pDS)
	{

		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		
		OGL4DepthStencilBuffer* pGLTex = (OGL4DepthStencilBuffer*)pDS.get();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,  pGLTex->GetDepthStencilBufferObject(), 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_pDS = pDS;
	}
	DepthStencilBufferPtr OGL4RenderTexture::GetDepthStencilBuffer()
	{
		return m_pDS;
	}
	GLuint OGL4RenderTexture::GetFBO()
	{
		return m_fbo;
	}
}

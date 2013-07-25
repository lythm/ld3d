#include "ogl4graphics_pch.h"
#include "OGL4RenderTexture.h"
#include "OGL4Texture.h"
#include "OGL4DepthStencilBuffer.h"

namespace ld3d
{
	static GLenum s_draw_buffers[] = 
	{ 
		GL_COLOR_ATTACHMENT0, 
		GL_COLOR_ATTACHMENT1, 
		GL_COLOR_ATTACHMENT2, 
		GL_COLOR_ATTACHMENT3, 
		GL_COLOR_ATTACHMENT4, 
		GL_COLOR_ATTACHMENT5, 
		GL_COLOR_ATTACHMENT6, 
		GL_COLOR_ATTACHMENT7, 
		GL_COLOR_ATTACHMENT8, 
		GL_COLOR_ATTACHMENT9, 
		GL_COLOR_ATTACHMENT10, 
		GL_COLOR_ATTACHMENT11, 
		GL_COLOR_ATTACHMENT12, 
		GL_COLOR_ATTACHMENT13, 
		GL_COLOR_ATTACHMENT14, 
		GL_COLOR_ATTACHMENT15, 
	};
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

		for(auto v : m_texs)
		{
			v->Release();
		}

		m_texs.clear();

		if(m_pDS)
		{
			m_pDS->Release();
			m_pDS.reset();
		}
	}

	int	OGL4RenderTexture::GetTextureCount()
	{
		return (int)m_texs.size();
	}
	void OGL4RenderTexture::AttachTexture(TexturePtr pTex)
	{
		if(pTex == nullptr)
		{
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		OGL4Texture* pGLTex = (OGL4Texture*)pTex.get();
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (int)m_texs.size(), pGLTex->GetTextureObject(), 0);

		m_texs.push_back(pTex);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	TexturePtr OGL4RenderTexture::GetTexture(int index)
	{
		return m_texs[index];
	}
	void OGL4RenderTexture::AttachDepthStencilBuffer(DepthStencilBufferPtr pDS)
	{

		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		OGL4DepthStencilBuffer* pGLTex = (OGL4DepthStencilBuffer*)pDS.get();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, pGLTex->GetAttachPoint(),  GL_RENDERBUFFER, pGLTex->GetDepthStencilBufferObject());

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
	void OGL4RenderTexture::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glDrawBuffers(m_texs.size(), s_draw_buffers);
	}
}

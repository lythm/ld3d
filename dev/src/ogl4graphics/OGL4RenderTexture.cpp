#include "ogl4graphics_pch.h"
#include "OGL4RenderTexture.h"
#include "OGL4Texture.h"

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
		return true;
	}
	void OGL4RenderTexture::Release()
	{
		m_texs.clear();
	}
		
	int	OGL4RenderTexture::GetTextureCount()
	{
		return (int)m_texs.size();
	}
	void OGL4RenderTexture::AddTexture(Texture2Ptr pTex)
	{
		m_texs.push_back(pTex);
	}

	Texture2Ptr OGL4RenderTexture::GetTexture(int index)
	{
		return m_texs[index];
	}
	void OGL4RenderTexture::SetDepthStencilBuffer(DepthStencilBufferPtr pDS)
	{
		m_pDS = pDS;
	}
	DepthStencilBufferPtr OGL4RenderTexture::GetDepthStencilBuffer()
	{
		return m_pDS;
	}
}
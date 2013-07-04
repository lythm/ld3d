#include "ogl4graphics_pch.h"
#include "OGL4RenderTexture.h"

namespace ld3d
{
	OGL4RenderTexture::OGL4RenderTexture(void)
	{
	}


	OGL4RenderTexture::~OGL4RenderTexture(void)
	{
	}
	int	OGL4RenderTexture::GetRenderTargetCount()
	{
		return 0;
	}
	TexturePtr OGL4RenderTexture::AsTexture(int index)
	{
		return TexturePtr();
	}
	void OGL4RenderTexture::SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer)
	{
	}
	DepthStencilBufferPtr OGL4RenderTexture::GetDepthStencilBuffer()
	{
		return DepthStencilBufferPtr();
	}
	void OGL4RenderTexture::Release()
	{
	}
	int	OGL4RenderTexture::GetWidth(int index)
	{
		return 0;
	}
	int	OGL4RenderTexture::GetHeight(int index)
	{
		return 0;
	}
}
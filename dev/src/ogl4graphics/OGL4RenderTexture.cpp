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
	bool OGL4RenderTexture::Create(int w, int h, G_FORMAT format)
	{
		return true;
	}
	void OGL4RenderTexture::Release()
	{
	}
		
	int OGL4RenderTexture::GetWidth()
	{
		return 0;
	}
	int OGL4RenderTexture::GetHeight()
	{
		return 0;
	}
	TexturePtr OGL4RenderTexture::AsTexture()
	{
		return TexturePtr();
	}
}
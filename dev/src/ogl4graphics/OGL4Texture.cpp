#include "ogl4graphics_pch.h"
#include "OGL4Texture.h"
#include "OGL4Covert.h"

namespace ld3d
{
	OGL4Texture::OGL4Texture(void)
	{
		m_texture				= 0;
		m_width					= 0;
		m_height				= 0;
		m_type					= TEX_UNKNOWN;
	}


	OGL4Texture::~OGL4Texture(void)
	{
	}
	TEXTURE_TYPE OGL4Texture::GetType()
	{
		return TEX_2D;
	}
	void OGL4Texture::Release()
	{
		glDeleteTextures(1, &m_texture);
	}
	bool OGL4Texture::Create(TEXTURE_TYPE type, G_FORMAT format, int w, int h)
	{
		glGenTextures(1, &m_texture);

		GLenum target = OGL4Covert::TexTypeToGLTarget(type);

		glBindTexture(target, m_texture);
		glTexImage2D(target, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


		return true;
	}
}

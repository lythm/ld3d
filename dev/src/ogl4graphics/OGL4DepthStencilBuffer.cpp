#include "ogl4graphics_pch.h"
#include "OGL4DepthStencilBuffer.h"
#include "OGL4Convert.h"

namespace ld3d
{
	OGL4DepthStencilBuffer::OGL4DepthStencilBuffer(void)
	{
		m_buffer = 0;
	}


	OGL4DepthStencilBuffer::~OGL4DepthStencilBuffer(void)
	{
	}
	void OGL4DepthStencilBuffer::Release()
	{
		glDeleteRenderbuffers(1, &m_buffer);
		m_buffer = 0;
	}
	bool OGL4DepthStencilBuffer::Create(G_FORMAT format, int w, int h)
	{
		glGenRenderbuffers(1, &m_buffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_buffer);
		glRenderbufferStorage(GL_RENDERBUFFER, OGL4Convert::TextureFormatToGL(format), w, h);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		return true;
	}
	GLuint OGL4DepthStencilBuffer::GetDepthStencilBufferObject()
	{
		return m_buffer;
	}
}

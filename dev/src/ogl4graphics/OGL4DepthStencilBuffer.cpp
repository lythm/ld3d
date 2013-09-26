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
	bool OGL4DepthStencilBuffer::CreateMS(G_FORMAT format, int w, int h, int samples)
	{
		glGenRenderbuffers(1, &m_buffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_buffer);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, OGL4Convert::TextureFormatToGL(format), w, h);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		m_format = format;
		return true;
	}
	bool OGL4DepthStencilBuffer::Create(G_FORMAT format, int w, int h)
	{
		glGenRenderbuffers(1, &m_buffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_buffer);
		glRenderbufferStorage(GL_RENDERBUFFER, OGL4Convert::TextureFormatToGL(format), w, h);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		m_format = format;
		return true;
	}
	GLuint OGL4DepthStencilBuffer::GetDepthStencilBufferObject()
	{
		return m_buffer;
	}
	GLenum OGL4DepthStencilBuffer::GetAttachPoint()
	{
		switch(m_format)
		{
		case G_FORMAT_D32_FLOAT:
			return GL_DEPTH_ATTACHMENT;
		case G_FORMAT_D24_UNORM_S8_UINT:
			return GL_DEPTH_STENCIL_ATTACHMENT;
		case G_FORMAT_D16_UNORM:
			return GL_DEPTH_ATTACHMENT;
		case G_FORMAT_D32_FLOAT_S8X24_UINT:
			return GL_DEPTH_STENCIL_ATTACHMENT;
		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
}

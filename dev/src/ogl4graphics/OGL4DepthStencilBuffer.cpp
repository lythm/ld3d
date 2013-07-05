#include "ogl4graphics_pch.h"
#include "OGL4DepthStencilBuffer.h"

namespace ld3d
{
	OGL4DepthStencilBuffer::OGL4DepthStencilBuffer(void)
	{
		m_buffer = GL_INVALID_ENUM;
	}


	OGL4DepthStencilBuffer::~OGL4DepthStencilBuffer(void)
	{
	}
	void OGL4DepthStencilBuffer::Release()
	{
	}
	bool OGL4DepthStencilBuffer::Create()
	{
		return true;
	}
}

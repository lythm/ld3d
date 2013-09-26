#pragma once
#include "core/DepthStencilBuffer.h"

namespace ld3d
{

	class OGL4DepthStencilBuffer : public DepthStencilBuffer
	{
	public:
		OGL4DepthStencilBuffer(void);
		virtual ~OGL4DepthStencilBuffer(void);

		void							Release();

		bool							Create(G_FORMAT format, int w, int h);
		bool							CreateMS(G_FORMAT format, int w, int h, int samples);
		GLenum							GetAttachPoint();
		GLuint							GetDepthStencilBufferObject();
	private:
		GLuint							m_buffer;

		G_FORMAT						m_format;
	};
}

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

		bool							Create();

	private:
		GLenum							m_buffer;
	};


}
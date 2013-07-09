#pragma once
#include "core\GPUBuffer.h"

namespace ld3d
{
	class OGL4Buffer : public GPUBuffer
	{
	public:
		OGL4Buffer(void);
		virtual ~OGL4Buffer(void);

		bool											Create(BUFFER_TYPE type, uint32 bytes, void* initData, bool dynamic);
		void*											Map(MAP_HINT hint);
		void											Unmap();
		void											Release();
		uint64											GetBytes() const;
		GLuint											GetBufferObject();
	private:
		
		GLuint											m_buffer;
		uint32											m_bytes;
		bool											m_bDynamic;
		BUFFER_TYPE										m_type;

	};
}

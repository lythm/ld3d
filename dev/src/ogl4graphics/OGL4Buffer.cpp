#include "ogl4graphics_pch.h"
#include "OGL4Buffer.h"
#include "OGL4Convert.h"


namespace ld3d
{
	OGL4Buffer::OGL4Buffer(void)
	{
		m_buffer				= 0;
		m_bytes					= 0;
		m_bDynamic				= false;
		m_type					= BT_UNKNOWN;
	}


	OGL4Buffer::~OGL4Buffer(void)
	{
	}
	void* OGL4Buffer::Map(MAP_HINT hint)
	{
		
		GLenum target = OGL4Convert::BufferTypeToGLTarget(m_type);
		
		glBindBuffer(target, m_buffer);

		void* data = nullptr;
		switch(hint)
		{
		case MAP_DISCARD:
			data = glMapBufferRange(target, 0, m_bytes, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
			break;
		case MAP_NO_OVERWRITE:
			data = glMapBufferRange(target, 0, m_bytes, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			break;
		case MAP_DEFAULT:
			data = glMapBufferRange(target, 0, m_bytes, GL_MAP_WRITE_BIT);
			break;
		}
		return data;
	}
	void OGL4Buffer::Unmap()
	{
		GLenum target = OGL4Convert::BufferTypeToGLTarget(m_type);
		glUnmapBuffer(target);
		glBindBuffer(target, 0);
	}
	void OGL4Buffer::Release()
	{
		glDeleteBuffers(1, &m_buffer);
		m_buffer = -1;
	}
	bool OGL4Buffer::Create(BUFFER_TYPE type, uint32 bytes, void* initData, bool dynamic)
	{
		m_type = type;
		m_bytes = bytes;
		m_bDynamic = dynamic;

		glGenBuffers(1, &m_buffer);
		GLenum target = OGL4Convert::BufferTypeToGLTarget(type);
		
		glBindBuffer(target, m_buffer);
		
		glBufferData(target, bytes, initData, dynamic ? GL_STREAM_DRAW : GL_STATIC_DRAW);

		glBindBuffer(target, 0);

		return true;
	}
	uint64 OGL4Buffer::GetBytes() const
	{
		return m_bytes;
	}
	GLuint OGL4Buffer::GetBufferObject()
	{
		return m_buffer;
	}
	
}

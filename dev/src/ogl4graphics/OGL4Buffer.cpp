#include "ogl4graphics_pch.h"
#include "OGL4Buffer.h"
#include "OGL4Covert.h"


namespace ld3d
{
	OGL4Buffer::OGL4Buffer(void)
	{
		m_buffer				= -1;
		m_bytes					= 0;
		m_bDynamic				= false;
		m_type					= BT_UNKNOWN;
	}


	OGL4Buffer::~OGL4Buffer(void)
	{
	}
	void* OGL4Buffer::Map(MAP_HINT hint)
	{
		Bind();
		GLenum target = OGL4Covert::BufferTypeToGLTarget(m_type);
		
		void* data = nullptr;
		switch(hint)
		{
		case MAP_DISCARD:
			glBufferData(target, m_bytes, NULL, m_bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

			data = glMapBufferRange(target, 0, m_bytes, GL_MAP_WRITE_BIT);
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
		GLenum target = OGL4Covert::BufferTypeToGLTarget(m_type);
		glUnmapBuffer(target);
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
		Bind();

		glBufferData(GL_ARRAY_BUFFER, bytes, initData, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

		return true;
	}
	GLuint OGL4Buffer::GetBufferObject()
	{
		return m_buffer;
	}
	void OGL4Buffer::Bind()
	{
		GLenum target = OGL4Covert::BufferTypeToGLTarget(m_type);
		glBindBuffer(target, m_buffer);
	}
	
}

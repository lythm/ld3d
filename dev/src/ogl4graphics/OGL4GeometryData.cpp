#include "ogl4graphics_pch.h"
#include "OGL4GeometryData.h"
#include "OGL4Buffer.h"
#include "OGL4Convert.h"
namespace ld3d
{
	OGL4GeometryData::OGL4GeometryData(void)
	{
		m_vao = 0;
		m_indexType = GL_UNSIGNED_SHORT;
		m_primType = GL_TRIANGLES;
		m_vbOffset = 0;
	}


	OGL4GeometryData::~OGL4GeometryData(void)
	{
	}
	bool OGL4GeometryData::Create()
	{
		glGenVertexArrays(1, &m_vao);

		return true;
	}
	void OGL4GeometryData::Release()
	{
		if(m_pVertexBuffer)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer.reset();
		}
		if(m_pIndexBuffer)
		{
			m_pIndexBuffer->Release();
			m_pIndexBuffer.reset();
		}

		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
	void OGL4GeometryData::Bind()
	{
		glBindVertexArray(m_vao);
	}

	void OGL4GeometryData::AttachVertexBuffer(GPUBufferPtr pBuffer, const VertexLayout& layout)
	{
		if(m_pVertexBuffer)
		{
			m_pVertexBuffer->Release();
		}
		m_pVertexBuffer = pBuffer;

		SetVertexLayout(layout);
	}
	void OGL4GeometryData::AttachIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT format)
	{
		if(m_pIndexBuffer)
		{
			m_pIndexBuffer->Release();
		}
		m_pIndexBuffer = pBuffer;

		switch(format)
		{
		case G_FORMAT_R32_UINT:
			m_indexType = GL_UNSIGNED_INT;
			break;
		case G_FORMAT_R16_UINT:
			m_indexType = GL_UNSIGNED_SHORT;
			break;
		default:
			assert(0);
			m_indexType = GL_UNSIGNED_SHORT;
			break;
		}

		OGL4BufferPtr pOGLBuffer = std::dynamic_pointer_cast<OGL4Buffer>(m_pIndexBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pOGLBuffer->GetBufferObject());
	}

	GPUBufferPtr OGL4GeometryData::GetIndexBuffer()
	{
		return m_pIndexBuffer;
	}
	GPUBufferPtr OGL4GeometryData::GetVertexBuffer()
	{
		return m_pVertexBuffer;
	}
	void OGL4GeometryData::SetVertexBufferOffset(unsigned int offset)
	{
		m_vbOffset = offset;
		SetVertexLayout(m_layout);
	}
	void OGL4GeometryData::BeginGeometry(PRIMITIVE_TYPE prim)
	{
		SetPrimitiveType(prim);
		glBindVertexArray(m_vao);
	}
	void OGL4GeometryData::EndGeometry()
	{
		glBindVertexArray(0);
	}
	const VertexLayout&	OGL4GeometryData::GetVertexLayout() const
	{
		return m_layout;
	}
	void OGL4GeometryData::SetVertexLayout(const VertexLayout& layout)
	{
		m_layout = layout;

		unsigned int stride = m_layout.VertexStride();

		OGL4BufferPtr pOGLBuffer = std::dynamic_pointer_cast<OGL4Buffer>(m_pVertexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, pOGLBuffer->GetBufferObject());

		unsigned int offset = 0;
		for(unsigned int i = 0; i < m_layout.AttrCount(); ++i)
		{
			glEnableVertexAttribArray(i);

			G_FORMAT type = m_layout.AttrType(i);

			unsigned int value_count = 0;
			GLenum gltype = GL_INVALID_ENUM;

			assert(OGL4Convert::FormatToGLVertexAttr(type, value_count, gltype));

			glVertexAttribPointer(i, value_count, gltype, false, stride, (GLvoid*)(m_vbOffset + offset));

			offset += m_layout.TypeBytes(type);
		}
	}
	GLenum OGL4GeometryData::GetIndexType() const
	{
		return m_indexType;
	}
	void OGL4GeometryData::SetPrimitiveType(PRIMITIVE_TYPE type)
	{
		m_primType = OGL4Convert::PrimitiveTypeToGL(type);
	}
	GLenum OGL4GeometryData::GetPrimitiveType() const
	{
		return m_primType;
	}
}

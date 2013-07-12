#pragma once


#include "core/GeometryData.h"



namespace ld3d
{
	class OGL4GeometryData : public GeometryData
	{
	public:
		OGL4GeometryData(void);
		virtual ~OGL4GeometryData(void);


		

		void													BeginGeometry(PRIMITIVE_TYPE prim);

		bool													AllocVertexBuffer(uint32 bytes, void* initData, bool dynamic, const VertexLayout& layout);
		bool													AllocIndexBuffer(uint32 bytes, void* initData, bool dynamic, G_FORMAT format);
		void													AttachVertexBuffer(GPUBufferPtr pBuffer, const VertexLayout& layout);
		void													AttachIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT format);
		
		GPUBufferPtr											GetIndexBuffer();
		GPUBufferPtr											GetVertexBuffer();

		void													SetVertexBufferOffset(unsigned int offset);
		void													SetVertexLayout(const VertexLayout& layout);

		void													EndGeometry();

		void													Release();
		void													SetPrimitiveType(PRIMITIVE_TYPE type);
		const VertexLayout&										GetVertexLayout() const;


		bool													Create();
		void													Bind();
		GLenum													GetIndexType() const;
		GLenum													GetPrimitiveType() const;
		
	private:
		GLuint													m_vao;

		GPUBufferPtr											m_pVertexBuffer;
		GPUBufferPtr											m_pIndexBuffer;
		VertexLayout											m_layout;
		GLenum													m_indexType;
		GLenum													m_primType;
		unsigned int											m_vbOffset;

	};
}

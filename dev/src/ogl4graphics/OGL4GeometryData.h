#pragma once


#include "core/GeometryData.h"



namespace ld3d
{
	class OGL4GeometryData : public GeometryData
	{
	public:
		OGL4GeometryData(void);
		virtual ~OGL4GeometryData(void);


		bool													Create();
		void													Bind();

		void													BeginGeometry();

		void													AttachVertexBuffer(GPUBufferPtr pBuffer, const VertexLayout& layout);
		void													AttachIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT format);
		
		GPUBufferPtr											GetIndexBuffer();
		GPUBufferPtr											GetVertexBuffer();

		void													SetVertexBufferOffset(unsigned int offset);
		void													SetVertexLayout(const VertexLayout& layout);

		void													EndGeometry();

		void													Release();
		
		const VertexLayout&										GetVertexLayout() const;

		GLenum													GetIndexType() const;
	private:
		GLenum													m_vao;

		GPUBufferPtr											m_pVertexBuffer;
		GPUBufferPtr											m_pIndexBuffer;
		VertexLayout											m_layout;
		GLenum													m_indexType;

		unsigned int											m_vbOffset;
	};
}

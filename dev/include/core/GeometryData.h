#pragma once

#include "core/VertexFormat.h"

namespace ld3d
{
	class GeometryData
	{
	public:


		virtual void													Release()												= 0;

		virtual void													BeginGeometry(PRIMITIVE_TYPE prim)						= 0;

		virtual bool													AllocVertexBuffer(uint32 bytes, 
																			void* initData, 
																			bool dynamic, 
																			const VertexLayout& layout)							= 0;
		virtual bool													AllocIndexBuffer(uint32 bytes, 
																			void* initData, 
																			bool dynamic, 
																			G_FORMAT format)									= 0;
		virtual void													AttachVertexBuffer(GPUBufferPtr pBuffer, 
																			const VertexLayout& layout)							= 0;
		virtual void													AttachIndexBuffer(GPUBufferPtr pBuffer, 
																			G_FORMAT format)									= 0;
		
		virtual GPUBufferPtr											GetIndexBuffer()										= 0;
		virtual GPUBufferPtr											GetVertexBuffer()										= 0;

		virtual void													SetVertexBufferOffset(unsigned int offset, 
																			const VertexLayout& layout)							= 0;

		virtual void													SetVertexLayout(const VertexLayout& layout)				= 0;

		virtual void													EndGeometry()											= 0;
		virtual void													SetPrimitiveType(PRIMITIVE_TYPE type)					= 0;
		virtual const VertexLayout&										GetVertexLayout() const									= 0;


		virtual ~GeometryData(void){}
		GeometryData(void){}
	};
}
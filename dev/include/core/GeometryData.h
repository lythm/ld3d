#pragma once

#include "core/VertexFormat.h"

namespace ld3d
{
	class GeometryData
	{
	public:


		virtual void													Release()									= 0;

		virtual void													BeginGeometry()								= 0;

		virtual void													AttachVertexBuffer(GPUBufferPtr pBuffer, 
																			const VertexLayout& layout)				= 0;
		virtual void													AttachIndexBuffer(GPUBufferPtr pBuffer, 
																			G_FORMAT format)						= 0;
		
		virtual GPUBufferPtr											GetIndexBuffer()							= 0;
		virtual GPUBufferPtr											GetVertexBuffer()							= 0;

		virtual void													SetVertexBufferOffset(unsigned int offset)	= 0;
		virtual void													SetVertexLayout(const VertexLayout& layout)	= 0;

		virtual void													EndGeometry()								= 0;

		virtual const VertexLayout&										GetVertexLayout() const						= 0;
	protected:
		GeometryData(void){}

		virtual ~GeometryData(void){}
	};


}
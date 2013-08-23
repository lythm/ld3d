#pragma once

#include "core/RenderData.h"

namespace ld3d
{
	class _DLL_CLASS BBoxRenderData
	{
	public:
		BBoxRenderData(void);
		virtual ~BBoxRenderData(void);

		bool													Initialize(Sys_GraphicsPtr pGraphics);
		void													Release();

//		void													Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial = MaterialPtr());
		MaterialPtr												GetMaterial();
		math::Matrix44											GetWorldMatrix();
		bool													IsDeferred();

		void													SetBBox(const math::AABBox& box);
		void													SetWorldMatrix(const math::Matrix44& world);

	private:
		void													_fill_vb();
	private:
		GPUBufferPtr											m_pVertexBuffer;
		MaterialPtr												m_pMaterial;
		math::AABBox											m_bbox;
		math::Matrix44											m_world;
	};


}
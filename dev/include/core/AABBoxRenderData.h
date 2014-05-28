#pragma once

namespace ld3d
{
	class _DLL_CLASS AABBoxRenderData
	{
	public:
		AABBoxRenderData(void);
		virtual ~AABBoxRenderData(void);

		bool													Initialize(RenderManagerPtr pRenderManager);
		void													Release();


		RenderDataPtr											GetRenderData();

		void													SetBox(const math::AABBox& box);
		void													SetWorldMatrix(const math::Matrix44& world);
	private:
		void													UpdateGeometry();

	private:
		RenderDataPtr											m_pRenderData;
		math::AABBox											m_box;
	};
}

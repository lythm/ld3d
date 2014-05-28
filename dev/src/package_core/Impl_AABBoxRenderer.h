#pragma once

#include "packages/core/AABBoxRenderer.h"
namespace ld3d
{
	class Impl_AABBoxRenderer : public AABBoxRenderer
	{
	public:
		Impl_AABBoxRenderer(GameObjectManagerPtr pManager);
		virtual ~Impl_AABBoxRenderer(void);


		bool													OnAttach();
		void													OnDetach();

		void													Update(float dt);

		void													SetAABBox(const math::AABBox& box);

	private:
		void													on_event_frustum_cull(EventPtr pEvent);
		void													ResetRenderData();
	private:
		AABBoxRenderDataPtr										m_pRD;
		EventHandlerID											m_hFrustumCull;
		RenderManagerPtr										m_pRenderManager;
	};


}
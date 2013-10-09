#pragma once

#include "packages/core/MeshRenderer.h"

namespace ld3d
{

	class Impl_MeshRenderer : public MeshRenderer
	{
	public:
		Impl_MeshRenderer(GameObjectManagerPtr pManager);
		virtual ~Impl_MeshRenderer(void);

		void													Update(float dt);

		void													Reset(MeshDataPtr pMD);
		const bool&												IsDeferred();
		void													SetDeferred(const bool& b);

		RenderManagerPtr										GetRenderManager(){return m_pRenderManager;}

	private:
		bool													OnAttach();
		void													OnDetach();

		void													on_event_frustum_cull(EventPtr pEvent);
	private:

		EventHandlerID											m_hFrustumCull;

		RenderManagerPtr										m_pRenderManager;

		std::vector<RenderDataPtr>								m_Subsets;
		bool													m_deferred;
	};

}

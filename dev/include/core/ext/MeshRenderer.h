#pragma once

#include "core/GameObjectComponent.h"
#include "core/RenderData.h"
#include "core/g_format.h"
#include "core/VertexFormat.h"

namespace ld3d
{

	class EXPORT_CLASS MeshRenderer : public GameObjectComponent
	{
	public:
		MeshRenderer(GameObjectManagerPtr pManager);
		virtual ~MeshRenderer(void);

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

		EventDispatcher::EventHandlerHandle						m_hFrustumCull;

		RenderManagerPtr										m_pRenderManager;

		std::vector<RenderDataPtr>								m_Subsets;
		bool													m_deferred;
	};

}

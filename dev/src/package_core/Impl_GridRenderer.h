#pragma once

#include "packages/core/GridRenderer.h"
namespace ld3d
{

	class Impl_GridRenderer : public GridRenderer
	{
	public:
		Impl_GridRenderer(GameObjectManagerPtr pManager);
		virtual ~Impl_GridRenderer(void);

		bool													OnAttach();
		void													OnDetach();

		void													Update(float dt);

		void													SetSize(uint32 size);
		void													SetGridSize(uint32 gridSize);

		uint32													GetSize();
		uint32													GetGridSize();
	private:
		void													on_event_frustum_cull(EventPtr pEvent);

		void													ResetGrid();
	private:
		EventHandlerID											m_hFrustumCull;
		RenderManagerPtr										m_pRenderManager;

		RenderDataPtr											m_pRenderData;

		int32													m_gridSize;
		int32													m_size;
	};
}


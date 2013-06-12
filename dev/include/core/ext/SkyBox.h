#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
{
	class SkyBox : public GameObjectComponent
	{
		class SkyBoxRenderData : public RenderData
		{
		public:

		private:

			GPUBufferPtr								m_pVB;
		};
	public:
		SkyBox(GameObjectManagerPtr pManager);
		virtual ~SkyBox(void);

		void										Update(float dt);

	private:
		bool										OnAttach();
		void										OnDetach();

		void										on_event_frustum_cull(EventPtr pEvent);

	private:
		


		EventDispatcher::EventHandlerHandle			m_hFrustumCull;
	};


}
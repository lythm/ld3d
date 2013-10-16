#pragma once

#include "packages/core/SkyBox.h"

namespace ld3d
{
	class Impl_SkyBox : public SkyBox
	{
	public:
		Impl_SkyBox(GameObjectManagerPtr pManager);
		virtual ~Impl_SkyBox(void);

		void										Update(float dt);

	private:
		bool										OnAttach();
		void										OnDetach();

		void										on_event_frustum_cull(EventPtr pEvent);

	private:
		
		RenderDataPtr								m_pRD;


		EventHandlerID								m_hFrustumCull;
	};


}
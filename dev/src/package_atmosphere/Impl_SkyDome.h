#pragma once

#include "atmosphere/SkyDome.h"

namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{
			class Impl_SkyDome : public SkyDome
			{
			public:

				Impl_SkyDome(GameObjectManagerPtr pManager);
				virtual ~Impl_SkyDome(void);

				bool												OnAttach();
				void												OnDetach();
			private:

				bool												CreateSkyDome();
				void												on_event_frustum_cull(EventPtr pEvent);
			private:

				RenderDataPtr										m_pRD;
				EventHandlerID										m_hFrustumCull;

				MaterialParameterPtr								m_pWorldPos;
			};
		}
	}
}
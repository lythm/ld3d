#pragma once

#include "packages/core/Light_Spot.h"

namespace ld3d
{
	class Impl_Light_Spot : public Light_Spot
	{
	public:
		Impl_Light_Spot(GameObjectManagerPtr pManager);
		virtual ~Impl_Light_Spot(void);

		void										Update(float dt);
		SpotLightPtr								GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr								m_pRenderManager;
		SpotLightPtr								m_pLight;
	};


}
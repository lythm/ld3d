#pragma once

#include "packages/core/Light_Point.h"

namespace ld3d
{
	class Impl_Light_Point : public Light_Point
	{
	public:
		Impl_Light_Point(GameObjectManagerPtr pManager);
		virtual ~Impl_Light_Point(void);

		void										Update(float dt);
		PointLightPtr								GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );
	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr								m_pRenderManager;
		PointLightPtr								m_pLight;
	};

}
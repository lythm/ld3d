#pragma once

#include "packages/core/Light_Sky.h"

namespace ld3d
{
	class Impl_Light_Sky : public Light_Sky
	{
	public:
		Impl_Light_Sky(GameObjectManagerPtr pManager);
		virtual ~Impl_Light_Sky(void);

		void										Update(float dt);
		SkyLightPtr									GetLight();


		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr							m_pRenderManager;
		SkyLightPtr									m_pLight;
	};


}

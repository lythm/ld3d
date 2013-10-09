#pragma once

#include "packages/core/Light_Dir.h"

namespace ld3d
{
	class Impl_Light_Dir : public Light_Dir
	{
	public:
		Impl_Light_Dir(GameObjectManagerPtr pManager);
		virtual ~Impl_Light_Dir(void);

		void										Update(float dt);
		DirectionalLightPtr							GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr							m_pRenderManager;
		DirectionalLightPtr							m_pLight;
	};
}

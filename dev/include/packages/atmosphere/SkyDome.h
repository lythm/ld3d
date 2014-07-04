#pragma once

namespace ld3d
{
	namespace atmosphere
	{
		class SkyDome : public GameObjectComponent
		{
		public:
			SkyDome(GameObjectManagerPtr pManager) : GameObjectComponent("Atmosphere.SkyDome", pManager){}
			virtual ~SkyDome(void){}
		};

	}

}

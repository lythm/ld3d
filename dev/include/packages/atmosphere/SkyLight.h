#pragma once

namespace ld3d
{
	namespace atmosphere
	{
		class SkyLight : public GameObjectComponent
		{
		public:

			SkyLight(GameObjectManagerPtr pManager) : GameObjectComponent("Atmosphere.SkyLight", pManager){}
			virtual ~SkyLight(void){}

			virtual LightPtr									GetLight()													= 0;
			virtual void										EnableShadow(bool enable)									= 0;

			virtual void										SetLightDir(const math::Vector3& dir)						= 0;
			virtual const math::Vector3&						GetLightDir() const											= 0;
		};
	}
}

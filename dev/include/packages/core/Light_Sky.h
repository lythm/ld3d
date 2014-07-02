#pragma once

namespace ld3d
{
	class Light_Sky : public GameObjectComponent
	{
	public:
		Light_Sky(GameObjectManagerPtr pManager) : GameObjectComponent("SkyLight", pManager){}
		virtual ~Light_Sky(void){}

		virtual SkyLightPtr									GetLight()						= 0;
		virtual void										EnableShadow(bool enable)		= 0;
	};


}

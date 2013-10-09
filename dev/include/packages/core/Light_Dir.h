#pragma once

namespace ld3d
{
	class Light_Dir : public GameObjectComponent
	{
	public:
		Light_Dir(GameObjectManagerPtr pManager) : GameObjectComponent("DirectionalLight", pManager){}
		virtual ~Light_Dir(void){}

		virtual DirectionalLightPtr					GetLight()												= 0;

	};
}

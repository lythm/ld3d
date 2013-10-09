#pragma once


namespace ld3d
{
	class Light_Spot : public GameObjectComponent
	{
	public:
		Light_Spot(GameObjectManagerPtr pManager) : GameObjectComponent("SpotLight", pManager){}
		virtual ~Light_Spot(void){}

		virtual SpotLightPtr								GetLight()							= 0;
	};

}
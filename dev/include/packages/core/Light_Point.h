#pragma once


namespace ld3d
{
	class Light_Point : public GameObjectComponent
	{
	public:
		Light_Point(GameObjectManagerPtr pManager) : GameObjectComponent("PointLight", pManager){}
		virtual ~Light_Point(void){}
		virtual PointLightPtr						GetLight()						= 0;

	};

}
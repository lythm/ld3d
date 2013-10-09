#pragma once

namespace ld3d
{
	class CameraController_Orbit : public GameObjectComponent
	{
	public:
		CameraController_Orbit(GameObjectManagerPtr pManager) : GameObjectComponent("CameraOrbitController", pManager){}
		virtual ~CameraController_Orbit(void){}
	};
}
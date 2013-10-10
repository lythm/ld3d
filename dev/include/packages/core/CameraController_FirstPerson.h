#pragma once

namespace ld3d
{
	class CameraController_FirstPerson : public GameObjectComponent
	{
	public:

		CameraController_FirstPerson(GameObjectManagerPtr pManager) : GameObjectComponent("CameraFirstPersonController", pManager)
		{
		}

		virtual ~CameraController_FirstPerson(void)
		{
		}
	};


}
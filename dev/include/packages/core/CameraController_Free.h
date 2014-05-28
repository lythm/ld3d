#pragma once

namespace ld3d
{
	class CameraController_Free : public GameObjectComponent
	{
	public:


		virtual float										GetSpeed() const																= 0;
		virtual void										SetSpeed(float speed)															= 0;
		virtual void										Enable(bool enabled)															= 0;
	protected:
		CameraController_Free(GameObjectManagerPtr pManager) : GameObjectComponent("CameraFreeController", pManager){}

		virtual ~CameraController_Free(void){}
	};


}
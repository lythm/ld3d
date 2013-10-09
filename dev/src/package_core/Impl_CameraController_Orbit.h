#pragma once

#include "packages/core/CameraController_Orbit.h"


namespace ld3d
{
	class Impl_CameraController_Orbit : public CameraController_Orbit
	{
	public:
		Impl_CameraController_Orbit(GameObjectManagerPtr pManager);
		virtual ~Impl_CameraController_Orbit(void);


		void										Update(float dt);
		bool										OnAttach();
		void										OnDetach();

	private:
		void										_on_mouse_move(ld3d::EventPtr pEvent);
		void										_on_mouse_wheel(ld3d::EventPtr pEvent);

	private:

		EventHandlerID								m_moveId;
		EventHandlerID								m_wheelId;


	};


}
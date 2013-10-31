#pragma once


#include "packages/core/CameraController_FirstPerson.h"

namespace ld3d
{
	class Impl_CameraData;
	class Impl_CameraController_FirstPerson : public CameraController_FirstPerson
	{
	public:
		Impl_CameraController_FirstPerson(GameObjectManagerPtr pManager);
		virtual ~Impl_CameraController_FirstPerson(void);


		void										Update(float dt);

	private:

		bool										OnAttach();
		void										OnDetach();

		void										_on_mouse_move(ld3d::EventPtr pEvent);
		void										_on_mouse_wheel(ld3d::EventPtr pEvent);
		void										_on_key(ld3d::EventPtr pEvent);

		void										UpdateRotating(float dx, float dy);
		void										UpdateMoving(float dt);
	private:

		EventHandlerID								m_moveId;
		EventHandlerID								m_wheelId;
		EventHandlerID								m_keyId;

		int											m_x;
		int											m_y;

		bool										m_forward;
		bool										m_backward;
		bool										m_left;
		bool										m_right;

		std::shared_ptr<Impl_CameraData>			m_pCameraData;
	};
}
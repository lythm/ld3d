#pragma once


#include "packages/core/CameraController_Free.h"

namespace ld3d
{
	class Impl_CameraData;
	class Impl_CameraController_Free : public CameraController_Free
	{
	public:
		Impl_CameraController_Free(GameObjectManagerPtr pManager);
		virtual ~Impl_CameraController_Free(void);


		void										Update(float dt);

		float										GetSpeed() const;
		void										SetSpeed(float speed);

		void										Enable(bool enabled);
	private:

		bool										OnAttach();
		void										OnDetach();

		void										_on_mouse_move(EventPtr pEvent);
		void										_on_mouse_wheel(EventPtr pEvent);
		void										_on_key(EventPtr pEvent);

		void										UpdateRotating(float dx, float dy);
		void										UpdateMoving(float dt);

		void										CorrectPosition();
	private:

		EventHandlerID								m_moveId;
		EventHandlerID								m_wheelId;
		EventHandlerID								m_keyId;

		bool										m_forward;
		bool										m_backward;
		bool										m_left;
		bool										m_right;

		std::shared_ptr<Impl_CameraData>			m_pCameraData;

		float										m_speed;

		bool										m_enabled;
	};
}

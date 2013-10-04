#pragma once

namespace ld3d
{
	class CameraController_Orbit : public GameObjectComponent
	{
	public:
		CameraController_Orbit(GameObjectManagerPtr pManager);
		virtual ~CameraController_Orbit(void);


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
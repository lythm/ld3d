#include "core_ext_pch.h"
#include "packages/core/CameraController_Orbit.h"

namespace ld3d
{
	CameraController_Orbit::CameraController_Orbit(GameObjectManagerPtr pManager) : GameObjectComponent("CameraOrbitController", pManager)
	{
	}


	CameraController_Orbit::~CameraController_Orbit(void)
	{
	}
	void CameraController_Orbit::Update(float dt)
	{
	}
	bool CameraController_Orbit::OnAttach()
	{
		m_wheelId = m_pManager->AddEventHandler(EV_MOUSE_WHEEL, boost::bind(&CameraController_Orbit::_on_mouse_wheel, this, _1));
		m_moveId = m_pManager->AddEventHandler(EV_MOUSE_MOVE, boost::bind(&CameraController_Orbit::_on_mouse_move, this, _1));

		return true;
	}
	void CameraController_Orbit::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_wheelId);
		m_pManager->RemoveEventHandler(m_moveId);
	}

	void CameraController_Orbit::_on_mouse_move(ld3d::EventPtr pEvent)
	{
		using namespace ld3d;
		using namespace math;

		Event_MouseState* pState = (Event_MouseState*)pEvent.get();

		int x =  pState->mouse_state->x;
		int y =  pState->mouse_state->y;
		static int lastx = x;
		static int lasty = y;

		int dx = x - lastx;
		int dy = y - lasty;

		if(pState->mouse_state->LButtonDown())
		{
			GameObjectPtr pParent = m_pObject->GetParent();

			Matrix44 parent;
			parent.MakeIdentity();
			if(pParent)
			{
				parent = pParent->GetWorldTransform();
			}

			const Matrix44& local = m_pObject->GetLocalTransform();
			Vector3 axis_x = local.GetRow3(0);
			Vector3 axis_y = parent.GetRow3(1);
			m_pObject->SetLocalTransform(local *  MatrixRotationAxis(axis_x, dy * 0.01f) * MatrixRotationAxis(axis_y, dx * 0.01f));
		}

		lastx = x;
		lasty = y;

	}

	void CameraController_Orbit::_on_mouse_wheel(ld3d::EventPtr pEvent)
	{
		using namespace ld3d;
		using namespace math;

		Event_MouseState* pState = (Event_MouseState*)pEvent.get();


		int zDelta = pState->mouse_state->wheel;

		const Matrix44& local = m_pObject->GetLocalTransform();
		Vector3 axis_z = local.GetRow3(2);

		m_pObject->SetLocalTransform(local * MatrixTranslation(-0.01f * zDelta * axis_z));

	}

}

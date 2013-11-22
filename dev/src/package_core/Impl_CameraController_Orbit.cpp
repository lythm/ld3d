#include "core_ext_pch.h"
#include "Impl_CameraController_Orbit.h"

namespace ld3d
{
	Impl_CameraController_Orbit::Impl_CameraController_Orbit(GameObjectManagerPtr pManager) : CameraController_Orbit(pManager)
	{
	}


	Impl_CameraController_Orbit::~Impl_CameraController_Orbit(void)
	{
	}
	void Impl_CameraController_Orbit::Update(float dt)
	{
	}
	bool Impl_CameraController_Orbit::OnAttach()
	{
		m_wheelId = m_pManager->AddEventHandler(EV_MOUSE_WHEEL, boost::bind(&Impl_CameraController_Orbit::_on_mouse_wheel, this, _1));
		m_moveId = m_pManager->AddEventHandler(EV_MOUSE_MOVE, boost::bind(&Impl_CameraController_Orbit::_on_mouse_move, this, _1));

		return true;
	}
	void Impl_CameraController_Orbit::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_wheelId);
		m_pManager->RemoveEventHandler(m_moveId);
	}

	void Impl_CameraController_Orbit::_on_mouse_move(ld3d::EventPtr pEvent)
	{
		using namespace ld3d;
		using namespace math;

		Event_MouseState* pState = (Event_MouseState*)pEvent.get();

		int dx = pState->mouse_state->dx;
		int dy = pState->mouse_state->dy;

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

	}

	void Impl_CameraController_Orbit::_on_mouse_wheel(ld3d::EventPtr pEvent)
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

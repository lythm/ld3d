#include "core_ext_pch.h"
#include "Impl_CameraController_FirstPerson.h"

namespace ld3d
{
	Impl_CameraController_FirstPerson::Impl_CameraController_FirstPerson(GameObjectManagerPtr pManager) : CameraController_FirstPerson(pManager)
	{
		m_dx					= 0;
		m_dy					= 0;
		m_x						= -1;
		m_y						= -1;
		m_forward				= false;
		m_backward				= false;
		m_left					= false;
		m_right					= false;
	}
	
	Impl_CameraController_FirstPerson::~Impl_CameraController_FirstPerson(void)
	{
	}
	void Impl_CameraController_FirstPerson::Update(float dt)
	{
		UpdateRotating(dt);
		UpdateMoving(dt);
	}
	bool Impl_CameraController_FirstPerson::OnAttach()
	{
		m_dx					= 0;
		m_dy					= 0;
		m_x						= -1;
		m_y						= -1;
		m_forward				= false;
		m_backward				= false;
		m_left					= false;
		m_right					= false;


		m_wheelId = m_pManager->AddEventHandler(EV_MOUSE_WHEEL, boost::bind(&Impl_CameraController_FirstPerson::_on_mouse_wheel, this, _1));
		m_moveId = m_pManager->AddEventHandler(EV_MOUSE_MOVE, boost::bind(&Impl_CameraController_FirstPerson::_on_mouse_move, this, _1));
		m_keyId = m_pManager->AddEventHandler(EV_KEYBOARD_STATE, boost::bind(&Impl_CameraController_FirstPerson::_on_key, this, _1));
		
		return true;
	}
	void Impl_CameraController_FirstPerson::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_wheelId);
		m_pManager->RemoveEventHandler(m_moveId);
		m_pManager->RemoveEventHandler(m_keyId);
	}
	void Impl_CameraController_FirstPerson::_on_mouse_move(ld3d::EventPtr pEvent)
	{
		Event_MouseState* pState = (Event_MouseState*)pEvent.get();
		if(m_x == -1 || m_y == -1)
		{
			m_x = pState->mouse_state->x;
			m_y = pState->mouse_state->y;
			return;
		}

		m_dx += (pState->mouse_state->x - m_x);
		m_dy += (pState->mouse_state->y - m_y);

		m_x = pState->mouse_state->x;
		m_y = pState->mouse_state->y;
	}
	void Impl_CameraController_FirstPerson::_on_mouse_wheel(ld3d::EventPtr pEvent)
	{
	}
	void Impl_CameraController_FirstPerson::_on_key(ld3d::EventPtr pEvent)
	{
		using namespace math;

		Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

		m_forward						= pState->keyboard_state->KeyDown(key_w);
		m_backward						= pState->keyboard_state->KeyDown(key_s);
		m_left							= pState->keyboard_state->KeyDown(key_a);
		m_right							= pState->keyboard_state->KeyDown(key_d);

	}
	void Impl_CameraController_FirstPerson::UpdateMoving(float dt)
	{
		using namespace math;

		Matrix44 local = m_pObject->GetLocalTransform();

		Vector3 pos = local.GetRow3(3);

		Vector3 axis_x = local.GetRow3(0);
		axis_x.Normalize();
		Vector3 axis_y = local.GetRow3(1);
		axis_y.Normalize();
		Vector3 axis_z = local.GetRow3(2);
		axis_z.Normalize();

		float speed = 5.0f;

		float step = speed * dt;

		if(m_forward)
		{
			axis_z *= step;
			pos += axis_z;
		}

		if(m_backward)
		{
			axis_z *= -step;
			pos += axis_z;
		}


		if(m_left)
		{
			axis_x *= -step;
			pos += axis_x;
		}

		if(m_right)
		{
			axis_x *= step;
			pos += axis_x;
		}

		local.SetRow3(3, pos);
		m_pObject->SetLocalTransform(local);
	}
	void Impl_CameraController_FirstPerson::UpdateRotating(float dt)
	{
		using namespace math;

		Matrix44 local = m_pObject->GetLocalTransform();
		Matrix44 parent = MatrixIdentity();
		if(m_pObject->GetParent())
		{
			parent = m_pObject->GetParent()->GetWorldTransform();
		}

		Vector3 axis_x = local.GetRow3(0);
		axis_x.Normalize();
		Vector3 axis_y = parent.GetRow3(1);
		axis_y.Normalize();
		
		Vector3 pos = local.GetRow3(3);

		float dps = D2R(2);
		float step = dps * dt;

		local.SetRow3(3, Vector3(0, 0, 0));

		local = local * MatrixRotationAxis(axis_x, m_dy * step) * MatrixRotationAxis(axis_y, m_dx * step);
		local.SetRow3(3, pos);
		m_pObject->SetLocalTransform(local);
		m_dx = 0;
		m_dy = 0;
	}
}

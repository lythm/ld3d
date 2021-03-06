#include "core_ext_pch.h"
#include "Impl_CameraController_Free.h"
#include "Impl_CameraData.h"

namespace ld3d
{
	Impl_CameraController_Free::Impl_CameraController_Free(GameObjectManagerPtr pManager) : CameraController_Free(pManager)
	{
		m_forward				= false;
		m_backward				= false;
		m_left					= false;
		m_right					= false;

		m_speed					= 5.0f;
		m_enabled				= true;
	}
	
	Impl_CameraController_Free::~Impl_CameraController_Free(void)
	{
	}
	void Impl_CameraController_Free::Update(float dt)
	{
		UpdateMoving(dt);
	}
	bool Impl_CameraController_Free::OnAttach()
	{
		m_pCameraData = std::dynamic_pointer_cast<Impl_CameraData>(m_pObject->GetComponent("Camera"));

		m_forward				= false;
		m_backward				= false;
		m_left					= false;
		m_right					= false;


		m_wheelId = m_pManager->AddEventHandler(EV_MOUSE_WHEEL, boost::bind(&Impl_CameraController_Free::_on_mouse_wheel, this, _1));
		m_moveId = m_pManager->AddEventHandler(EV_MOUSE_MOVE, boost::bind(&Impl_CameraController_Free::_on_mouse_move, this, _1));
		m_keyId = m_pManager->AddEventHandler(EV_KEYBOARD_STATE, boost::bind(&Impl_CameraController_Free::_on_key, this, _1));
		
		return true;
	}
	void Impl_CameraController_Free::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_wheelId);
		m_pManager->RemoveEventHandler(m_moveId);
		m_pManager->RemoveEventHandler(m_keyId);
	}
	void Impl_CameraController_Free::_on_mouse_move(EventPtr pEvent)
	{
		if(m_enabled == false)
		{
			return;
		}
		Event_MouseState* pState = (Event_MouseState*)pEvent.get();
		
		float dx = pState->mouse_state->dx;
		float dy = pState->mouse_state->dy;

		UpdateRotating(dx, dy);

	}
	void Impl_CameraController_Free::_on_mouse_wheel(EventPtr pEvent)
	{
	}
	void Impl_CameraController_Free::_on_key(EventPtr pEvent)
	{
		if(m_enabled == false)
		{
			return;
		}
		using namespace math;

		Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

		m_forward						= pState->keyboard_state->KeyDown(key_w);
		m_backward						= pState->keyboard_state->KeyDown(key_s);
		m_left							= pState->keyboard_state->KeyDown(key_a);
		m_right							= pState->keyboard_state->KeyDown(key_d);

	}
	void Impl_CameraController_Free::UpdateMoving(float dt)
	{
		if(m_enabled == false)
		{
			return;
		}
		using namespace math;

		Matrix44 local = m_pObject->GetLocalTransform();

		Vector3 pos = local.GetRow3(3);

		Vector3 axis_x = local.GetRow3(0);
		axis_x.Normalize();
		Vector3 axis_y = local.GetRow3(1);
		axis_y.Normalize();
		Vector3 axis_z = local.GetRow3(2);
		axis_z.Normalize();

		

		float step = m_speed * dt;

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

	//	CorrectPosition();

		m_pCameraData->UpdateCamera();
	}
	void Impl_CameraController_Free::CorrectPosition()
	{
		math::Vector3 eye = m_pObject->GetWorldTransform().GetTranslation();

		math::Ray r(math::Vector3(eye.x, eye.y, eye.z), math::Vector3(0, -1, 0));


		PhysicsManagerPtr pPhy = m_pManager->GetPhysicsManager();

		Contact ret;
		while(true)
		{
			ret = pPhy->RayIntersect(r);

			if(r.GetT(ret.enter_point) >= 0)
			{
				break;
			}

			r.o = ret.enter_point;
		}

		if(ret.result == Contact::Yes)
		{
			m_pObject->SetTranslation(eye.x, ret.enter_point.y + 1.5, eye.z);
		}

	}
	void Impl_CameraController_Free::UpdateRotating(float dx, float dy)
	{
		if(m_enabled == false)
		{
			return;
		}
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

		local.SetRow3(3, Vector3(0, 0, 0));

		float step = D2R(0.1);

		local = local * MatrixRotationAxis(axis_x, dy * step) * MatrixRotationAxis(axis_y, dx * step);
		local.SetRow3(3, pos);
		m_pObject->SetLocalTransform(local);

		m_pCameraData->UpdateCamera();
	}
	float Impl_CameraController_Free::GetSpeed() const
	{
		return m_speed;
	}
	void Impl_CameraController_Free::SetSpeed(float speed)
	{
		m_speed = speed;
	}
	void Impl_CameraController_Free::Enable(bool enabled)
	{
		m_enabled = enabled;
	}
}

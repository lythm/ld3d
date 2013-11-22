#include "game_pch.h"
#include "PlayerController.h"
#include "packages/core/core_ext_all.h"


PlayerController::PlayerController(ld3d::GameObjectManagerPtr pManager) : GameObjectComponent("PlayerController", pManager)
{
	m_x						= -1;
	m_y						= -1;
	m_forward				= false;
	m_backward				= false;
	m_left					= false;
	m_right					= false;

}


PlayerController::~PlayerController(void)
{
}

void PlayerController::Update(float dt)
{
	using namespace ld3d;

	UpdateMoving(dt);

	GameObjectPtr pCamera = m_pObject->FindChild("Camera01");

	if(pCamera)
	{
		pCamera->Update(dt);
	}
}
bool PlayerController::OnAttach()
{
	using namespace ld3d;

	m_x						= -1;
	m_y						= -1;
	m_forward				= false;
	m_backward				= false;
	m_left					= false;
	m_right					= false;


	m_moveId = m_pManager->AddEventHandler(EV_MOUSE_MOVE, boost::bind(&PlayerController::_on_mouse_move, this, _1));
	m_keyId = m_pManager->AddEventHandler(EV_KEYBOARD_STATE, boost::bind(&PlayerController::_on_key, this, _1));

	return true;
}
void PlayerController::OnDetach()
{
	m_pManager->RemoveEventHandler(m_moveId);
	m_pManager->RemoveEventHandler(m_keyId);
}
void PlayerController::_on_mouse_move(ld3d::EventPtr pEvent)
{
	using namespace ld3d;

	Event_MouseState* pState = (Event_MouseState*)pEvent.get();
	if(m_x == -1 || m_y == -1)
	{
		m_x = pState->mouse_state->x;
		m_y = pState->mouse_state->y;
		return;
	}

	float dx = (pState->mouse_state->x - m_x);
	float dy = (pState->mouse_state->y - m_y);

	UpdateRotating(dx, dy);
	UpdateCamera(dx, dy);

	m_x = pState->mouse_state->x;
	m_y = pState->mouse_state->y;
}

void PlayerController::_on_key(ld3d::EventPtr pEvent)
{
	using namespace math;
	using namespace ld3d;

	Event_KeyboardState* pState = (Event_KeyboardState*)pEvent.get();

	m_forward						= pState->keyboard_state->KeyDown(key_w);
	m_backward						= pState->keyboard_state->KeyDown(key_s);
	m_left							= pState->keyboard_state->KeyDown(key_a);
	m_right							= pState->keyboard_state->KeyDown(key_d);

}
void PlayerController::UpdateMoving(float dt)
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

	//CorrectPosition();

}
void PlayerController::CorrectPosition()
{
	using namespace ld3d;

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
void PlayerController::UpdateCamera(float dx, float dy)
{
	using namespace ld3d;

	using namespace math;

	GameObjectPtr pCamera = m_pObject->FindChild("Camera01");

	if(pCamera == nullptr)
	{
		return;
	}
	Matrix44 local = pCamera->GetLocalTransform();
	Matrix44 parent = MatrixIdentity();
	if(pCamera->GetParent())
	{
		parent = pCamera->GetParent()->GetWorldTransform();
	}

	Vector3 axis_x = local.GetRow3(0);
	axis_x.Normalize();
	Vector3 axis_y = parent.GetRow3(1);
	axis_y.Normalize();

	Vector3 pos = local.GetRow3(3);

	local.SetRow3(3, Vector3(0, 0, 0));

	float step = D2R(0.1);

	//local = local * MatrixRotationAxis(axis_x, dy * step) * MatrixRotationAxis(axis_y, dx * step);

	local = local * MatrixRotationAxis(axis_x, dy * step);

	local.SetRow3(3, pos);
	pCamera->SetLocalTransform(local);

	CameraDataPtr pData = std::dynamic_pointer_cast<CameraData>(pCamera->GetComponent("Camera"));
	pData->UpdateCamera();
}
void PlayerController::UpdateRotating(float dx, float dy)
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

	local.SetRow3(3, Vector3(0, 0, 0));

	float step = D2R(0.1);

	//local = local * MatrixRotationAxis(axis_x, dy * step) * MatrixRotationAxis(axis_y, dx * step);

	local = local * MatrixRotationAxis(axis_y, dx * step);

	local.SetRow3(3, pos);
	m_pObject->SetLocalTransform(local);

}
void PlayerController::_on_collide(ld3d::CollisionDataPtr pCollider, const ld3d::Contact& contact)
{
	math::AABBox box;
	box.Make(math::Vector3(0, 0, 0), math::Vector3(1, 2, 1));
	
	math::TransformAABB(box, m_pObject->GetWorldTransform());

	using namespace math;
	Vector3 offset = box.GetExtent() * contact.normal * 0.5f;
	
	Vector3 new_center = contact.enter_point + offset;
	
	offset = new_center - box.GetCenter();
	
	//offset += Vector3(0.1, 1, 0.1);

	math::Matrix44 local = m_pObject->GetLocalTransform();

	local *= math::MatrixTranslation(offset);
	m_pObject->SetLocalTransform(local);
	pCollider->bound->worldMatrix = m_pObject->GetWorldTransform();
}


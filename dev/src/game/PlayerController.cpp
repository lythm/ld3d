#include "game_pch.h"
#include "PlayerController.h"
#include "packages/core/core_ext_all.h"


PlayerController::PlayerController(ld3d::GameObjectManagerPtr pManager) : GameObjectComponent("PlayerController", pManager)
{
	m_forward				= false;
	m_backward				= false;
	m_left					= false;
	m_right					= false;
	m_jump					= false;

	m_movingAcc				= 5;
	m_movingSpeed			= 5;
}


PlayerController::~PlayerController(void)
{
}

void PlayerController::Update(float dt)
{
	using namespace ld3d;


	m_lastPos = m_pObject->GetLocalTransform().GetTranslation();


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
	
	float dx = pState->mouse_state->dx;
	float dy = pState->mouse_state->dy;

	UpdateRotating(dx, dy);
	UpdateCamera(dx, dy);
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
	m_jump							= pState->keyboard_state->KeyDown(key_space);
	
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

	local = local * MatrixRotationAxis(axis_y, dx * step);

	local.SetRow3(3, pos);
	m_pObject->SetLocalTransform(local);

}
void PlayerController::_on_collide2(ld3d::CollisionDataPtr pCollider, const ld3d::Contact& contact)
{
	m_pObject->SetTranslation(m_lastPos);
	m_velocity = math::Vector3(0, 0, 0);
	m_pObject->Update(0);
	return;

	math::AABBox box;
	box.Make(math::Vector3(0, 0, 0), math::Vector3(1, 2, 1));
	
	math::TranslateAABB(box, m_pObject->GetWorldTransform());

	using namespace math;
	Vector3 offset = box.GetExtent() * contact.normal * 0.5f;
	
	Vector3 new_center = contact.enter_point + offset;
	
	offset = new_center - box.GetCenter();
	
	offset += Vector3(0.001, 0.001, 0.001);

	math::Matrix44 local = m_pObject->GetLocalTransform();

	local *= math::MatrixTranslation(offset);
	m_pObject->SetLocalTransform(local);
	pCollider->bound->worldMatrix = m_pObject->GetWorldTransform();

	if(contact.normal.y == 1.0f)
	{
		m_velocity = math::Vector3(0, 0, 0);
	}

	m_pObject->Update(0);
}


void PlayerController::_on_collide(ld3d::CollisionDataPtr pCollider, const ld3d::Contact& contact)
{

	using namespace math;
	
	


	math::Matrix44 local = m_pObject->GetLocalTransform();

	Vector3 curPos = local.GetTranslation();

	Vector3 dir = curPos - m_lastPos;

	Vector3 normal = contact.normal;
	float p = contact.penetration + 0.1;
	
	Vector3 offset;
	if(m_velocity == Vector3(0, 0, 0))
	{
		offset = p * normal;
	}
	else
	{

		Vector3 r = Reflect(dir, normal);

		float lr = Dot(r, normal);

		Vector3 t = (lr) * normal;

		Vector3 t1 = r - t;

		Vector3 t2 = t1 + p * normal;

		offset = t2;

		
		float vl = m_velocity.Length();

		if(t1 != Vector3(0, 0, 0))
		{
			t1.Normalize();
		}
		m_velocity = vl * t1;
	}



	local *= math::MatrixTranslation(offset);
	m_pObject->SetLocalTransform(local);
	pCollider->bound->worldMatrix = m_pObject->GetWorldTransform();

	m_pObject->Update(0);

	return;

//	int i_max = 0;
//	float l_max = -MATH_REAL_INFINITY;
//	for(int i = 0; i < 3; ++i)
//	{
//		if(abs(m_velocity[i]) > l_max)
//		{
//			l_max = abs(m_velocity[i]);
//			i_max = i;
//		}
//	}
//
//	Vector3 offset;
//	
//	offset[i_max] = contact.penetration[i_max];
//
////	offset[i_max] += 0.01;
//
//	math::Matrix44 local = m_pObject->GetLocalTransform();
//
//	local *= math::MatrixTranslation(-offset);
//	m_pObject->SetLocalTransform(local);
//	pCollider->bound->worldMatrix = m_pObject->GetWorldTransform();
//
//	m_velocity[i_max] = 0;
//
//	m_pObject->Update(0);

}

void PlayerController::UpdateVelocity(float dt)
{
	using namespace math;

	Vector2 acc_xz;

	acc_xz.y = m_forward ? 1 : m_backward ? -1 : 0;
	acc_xz.x = m_right ? 1 : m_left ? -1 : 0;
	
	if(acc_xz.Length() != 0)
	{
		acc_xz.Normalize();
		acc_xz *= m_movingAcc;
	}
	
	Vector2 v_xz(m_velocity.x, m_velocity.z);

	v_xz += acc_xz * dt;

	if(v_xz.Length() > m_movingSpeed)
	{
		v_xz.Normalize();
		v_xz *= m_movingSpeed;
	}
	
	float v_y = m_velocity.y + -9.8 * dt;

	m_velocity = Vector3(v_xz.x, v_y, v_xz.y);

	if(m_jump && m_velocity.y == 0)
	{
		m_velocity.y = 5;
	}
}
void PlayerController::UpdateMoving(float dt)
{
	using namespace math;

	UpdateVelocity(dt);
	
	Matrix44 local = m_pObject->GetLocalTransform();

	Vector3 v = m_velocity;

	TransformNormal(v, local);

	Vector3 pos = local.GetRow3(3);

	pos += v * dt;

	local.SetRow3(3, pos);
	m_pObject->SetLocalTransform(local);

	//CorrectPosition();
}

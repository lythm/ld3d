#pragma once

class PlayerController : public ld3d::GameObjectComponent
{
public:
	PlayerController(ld3d::GameObjectManagerPtr pManager);
	virtual ~PlayerController(void);

	void										Update(float dt);

	bool										OnAttach();
	void										OnDetach();

	void										_on_mouse_move(ld3d::EventPtr pEvent);
	void										_on_mouse_wheel(ld3d::EventPtr pEvent);
	void										_on_key(ld3d::EventPtr pEvent);

	void										UpdateRotating(float dx, float dy);
	void										UpdateMoving(float dt);
	void										UpdateCamera(float dx, float dy);

	void										UpdateVelocity(float dt);
	
	void										_on_collide2(ld3d::CollisionDataPtr pCollider, const ld3d::Contact& contact);
	void										_on_collide(ld3d::CollisionDataPtr pCollider, const ld3d::Contact& contact);
private:

	ld3d::EventHandlerID						m_moveId;
	ld3d::EventHandlerID						m_keyId;


	bool										m_forward;
	bool										m_backward;
	bool										m_left;
	bool										m_right;
	bool										m_jump;

	float										m_movingAcc;
	float										m_movingSpeed;
	math::Vector3								m_velocity;

	math::Vector3								m_lastPos;
};


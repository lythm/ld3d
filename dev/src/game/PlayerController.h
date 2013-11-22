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
	void										CorrectPosition();

	void										_on_collide(ld3d::CollisionDataPtr pCollider, const ld3d::Contact& contact);
private:

	ld3d::EventHandlerID						m_moveId;
	ld3d::EventHandlerID						m_keyId;

	int											m_x;
	int											m_y;

	bool										m_forward;
	bool										m_backward;
	bool										m_left;
	bool										m_right;
	

};


#pragma once

class OrbitCamera : public ld3d::Camera
{
public:
	OrbitCamera(void);
	virtual ~OrbitCamera(void);

	void				Update();

	math::Vector3		GetEyePos();
	math::Vector3		GetFocusPos();
	math::intersect_ret IntersectXZPlane(math::Vector3& target);
		
	void				SetViewPort(int cx, int cy);

	math::Ray			PickRay(int x, int y);

	void				SetFocusPos(const math::Vector3& at);
	void				SetEyePos(const math::Vector3& eye);
private:
	
	void				Rotate(int dx, int dy);
	void				Zoom(int d);
	void				Move(int dx, int dy);
private:

	int					m_vpw;
	int					m_vph;

	math::Vector3		m_at;
	math::Vector3		m_eye;
};


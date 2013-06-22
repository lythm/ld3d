#include "stdafx.h"
#include "OrbitCamera.h"



OrbitCamera::OrbitCamera(void)
{
	m_vpw				= 800;
	m_vph				= 600;


	SetEyePos(math::Vector3(0, 500, -500));
	SetFocusPos(math::Vector3(0, 0,0));
	
	LookAtLH(GetEyePos(), GetFocusPos(), math::Vector3(0, 1, 0));

}


OrbitCamera::~OrbitCamera(void)
{
}
void OrbitCamera::Update()
{
	using namespace ld3d;

	UpdateViewFrustum();

	return;
}
math::Vector3 OrbitCamera::GetEyePos()
{
	return m_eye;
}

math::intersect_ret OrbitCamera::IntersectXZPlane(math::Vector3& target)
{
	using namespace math;

	Ray r(GetEyePos(), GetAxisZ());
	Plane p(Vector3(0, 1, 0), Vector3(0, 0, 0));

	Real t = 0;

	intersect_ret ret = RayIntersectPlane(r, p, t);

	target = r.GetPos(t);

	return ret;
}
void OrbitCamera::SetViewPort(int cx, int cy)
{
	using namespace math;

	m_vpw = cx;
	m_vph = cy;
	float aspect = float(m_vpw) / float(m_vph);
	PerspectiveFovLH(1.0f/ 4.0f * MATH_PI, aspect, 0.1f, 10000);

}
void OrbitCamera::Rotate(int dx, int dy)
{
	using namespace math;

	Vector3 e = GetEyePos();
	Vector3 axis_x = GetAxisX();
	Vector3 axis_y = GetAxisY();

	Vector3 t = GetFocusPos();
	
	float factor = 0.5f / 108.0f;
	e = e - t;
	Matrix44 rot = MatrixRotationAxisY(dx * factor);

	rot = MatrixRotationAxis(axis_x, dy * factor) * rot;

	TransformCoord(e, rot);

	e += t;
	
	TransformNormal(axis_y, rot);

	SetEyePos(e);

	LookAtLH(e, t, axis_y);
}

void OrbitCamera::Zoom(int d)
{
	using namespace math;

	Vector3 e = GetEyePos();
	Vector3 t = GetFocusPos();
	
	Vector3 up = GetAxisY();

	Vector3 v = e - t;
	
	Real l = v.Length();

	Real offset = d /120.0f * l * 0.2f;

	l -= offset;

	l = l <= 1.0f ? 1.0f : l;

	v.Normalize();

	v *= l;

	e = t + v;

	SetEyePos(e);
	LookAtLH(e, t, up);

}
void OrbitCamera::Move(int dx, int dy)
{
	using namespace math;

	Matrix44 view = GetViewMatrix();

	Vector3 e = GetEyePos();
	Vector3 t = GetFocusPos();
		
	Vector3 v = e - t;
	
	Real l = v.Length();

	Real offset_x = dx /120.0f * l * 0.2f;
	Real offset_z = dy /120.0f * l * 0.2f;

	Vector3 axis_x = GetAxisX();
	Vector3 axis_z = GetAxisZ();
	Vector3 axis_y = GetAxisY();
	axis_z.y = 0;
	axis_z.Normalize();

	axis_x = -axis_x * offset_x * 0.5f;
	axis_z = axis_z * offset_z * 0.5;

	t += axis_x + axis_z;
	e += axis_x + axis_z;;

	
	SetEyePos(e);
	SetFocusPos(t);
	LookAtLH(e, t, axis_y);
}

math::Ray OrbitCamera::PickRay(int x, int y)
{
	using namespace math;

	return UnProject(x, y, m_vpw, m_vph, MatrixIdentity(), GetViewMatrix(), GetProjMatrix());
}
math::Vector3 OrbitCamera::GetFocusPos()
{
	return m_at;
}
void OrbitCamera::SetFocusPos(const math::Vector3& at)
{
	m_at = at;

	LookAtLH(GetEyePos(), GetFocusPos(), math::Vector3(0, 1, 0));
}
void OrbitCamera::SetEyePos(const math::Vector3& eye)
{
	m_eye = eye;

	LookAtLH(GetEyePos(), GetFocusPos(), math::Vector3(0, 1, 0));
}
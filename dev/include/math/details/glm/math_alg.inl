
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_major_storage.hpp>
#include <glm/gtc/quaternion.hpp>


namespace math
{
	inline
		Vector3 Cross(const Vector3& l, const Vector3& r)
	{
		
		const Real* p = glm::value_ptr(glm::cross(glm::vec3(l.x, l.y, l.z), glm::vec3(r.x, r.y, r.z)));

		
		return Vector3(p[0], p[1], p[2]);
	}
	
	inline
		Matrix44 MatrixRotationAxis(const Vector3& axis, Real rad)
	{
		glm::mat4x4 r = glm::rotate(glm::make_mat4(MatrixIdentity().m), rad, glm::make_vec3(axis.v));
		
		const Real* p = glm::value_ptr(r);

		return Matrix44(p);
	}
	inline
		Matrix44 MatrixRotationQuat(const Quat& q)
	{

		const Real* p = glm::value_ptr(glm::mat4_cast(glm::quat(q.x, q.y, q.z, q.w)));

		return Matrix44(p);
	}
	
	inline
		void TransformCoord(Vector2& v, const Matrix44& t)
	{
		glm::vec4 v1(v.x, v.y, 1, 1);
		glm::mat4 m1 = glm::make_mat4(t.m);

		v1 = m1 * v1;

		v.x = v1.x;
		v.y = v1.y;

	}
	inline
		void TransformCoord(Vector3& v, const Matrix44& t)
	{

		glm::vec4 v1(v.x, v.y, v.z, 1.0f);
		glm::mat4 m1 = glm::make_mat4(t.m);

		v1 = m1 * v1;

		v.x = v1.x;
		v.y = v1.y;
		v.z = v1.z;

	}
	inline
		void Transform(Vector4& v, const Matrix44& t)
	{

		glm::vec4 v1 = glm::make_vec4(v.v);
		glm::mat4 m1 = glm::make_mat4(t.m);

		v1 = m1 * v1;

		v.x = v1.x;
		v.y = v1.y;
		v.z = v1.z;
		v.w = v1.w;

	}
	inline
		void TransformNormal(Vector2& v, const Matrix44& t)
	{
		glm::vec4 v1(v.x, v.y, 0, 0);
		glm::mat4 m1 = glm::make_mat4(t.m);

		v1 = m1 * v1;

		v.x = v1.x;
		v.y = v1.y;
		
	}
	inline
		void	TransformNormal(Vector3& v, const Matrix44& t)
	{
		glm::vec4 v1(v.x, v.y, v.z, 0);
		glm::mat4 m1 = glm::make_mat4(t.m);

		v1 = m1 * v1;

		v.x = v1.x;
		v.y = v1.y;
		v.z = v1.z;

	}
	inline
		Matrix44 MatrixLookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		using namespace glm;

		vec3 e = make_vec3(eye.v);
	
		vec3 axis_z = normalize(make_vec3((at - eye).v));
		vec3 axis_x = normalize(cross(make_vec3(up.v), axis_z));
		vec3 axis_y = normalize(cross(axis_z, axis_x));

		mat4 Result(1);
		
		Result[0][0] = axis_x.x;
		Result[1][0] = axis_x.y;
		Result[2][0] = axis_x.z;
		Result[3][0] = -dot(axis_x,e);

		Result[0][1] = axis_y.x;
		Result[1][1] = axis_y.y;
		Result[2][1] = axis_y.z;
		Result[3][1] = -dot(axis_y, e);

		Result[0][2] = axis_z.x;
		Result[1][2] = axis_z.y;
		Result[2][2] = axis_z.z;
		Result[3][2] = -dot(axis_z, e);

		Result[0][3] = 0;
		Result[1][3] = 0;
		Result[2][3] = 0;
		Result[3][3] = 1;
		
		const Real* p = glm::value_ptr(Result);

		return Matrix44(p);
	}
	inline
		Matrix44 MatrixLookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		using namespace glm;

		vec3 e = make_vec3(eye.v);
	
		vec3 axis_z = normalize(make_vec3((eye - at).v));
		vec3 axis_x = normalize(cross(make_vec3(up.v), axis_z));
		vec3 axis_y = normalize(cross(axis_z, axis_x));

		mat4 Result(1);
		
		Result[0][0] = axis_x.x;
		Result[1][0] = axis_x.y;
		Result[2][0] = axis_x.z;
		Result[3][0] = -dot(axis_x,e);

		Result[0][1] = axis_y.x;
		Result[1][1] = axis_y.y;
		Result[2][1] = axis_y.z;
		Result[3][1] = -dot(axis_y, e);

		Result[0][2] = axis_z.x;
		Result[1][2] = axis_z.y;
		Result[2][2] = axis_z.z;
		Result[3][2] = -dot(axis_z, e);

		Result[0][3] = 0;
		Result[1][3] = 0;
		Result[2][3] = 0;
		Result[3][3] = 1;
		
		const Real* p = glm::value_ptr(Result);

		return Matrix44(p);
	}
	inline
		Matrix44 MatrixOrthoLH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 mat;

		mat.m11 = 2 / w;
		mat.m22 = 2 / h;
		mat.m33 = 1 / (zf - zn);
		mat.m34 = 0;
		mat.m43 = -zn / (zf - zn);
		mat.m44 = 1;
		return mat;
	}
	inline
		Matrix44 MatrixOrthoRH(Real w, Real h, Real zn, Real zf)
	{

		Matrix44 mat;

		mat.m11 = 2 / w;
		mat.m22 = 2 / h;
		mat.m33 = 1 / (zn - zf);
		mat.m34 = 0;
		mat.m43 = zn / (zn - zf);
		mat.m44 = 1;
		return mat;
		

	}
	inline
		Matrix44 MatrixPerspectiveLH(Real w, Real h, Real zn, Real zf)
	{
		
		Matrix44 mat;

		mat.m11 = 2 * zn / w;
		mat.m22 = 2 * zn / h;
		mat.m33 = zf / (zf - zn);
		mat.m34 = 1;
		mat.m43 = zn * zf / (zn - zf);

		return mat;
	}
	inline
		Matrix44 MatrixPerspectiveRH(Real w, Real h, Real zn, Real zf)
	{
		
		Matrix44 mat;

		mat.m11 = 2 * zn / w;
		mat.m22 = 2 * zn / h;
		mat.m33 = zf / (zn - zf);
		mat.m34 = -1;
		mat.m43 = zn * zf / (zn - zf);

		return mat;
	}
	inline
		Matrix44 MatrixPerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf)
	{
		Matrix44 mat;
		
		Real ys = 1.0f / tan(fov / 2.0f);
		Real xs = ys / aspect;

		
		//real t = real(tan(fov / 2.0));

		//real h = real(1.0) / t;
		//real w = real(1.0) / aspect * h;

		mat.m11 = xs;
		mat.m22 = ys;
		mat.m33 = zf / (zf - zn);
		mat.m34 = 1;
		mat.m43 = -zn * zf / (zf - zn);

		return mat;
	}
	inline
		Matrix44 MatrixPerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf)
	{
		
		Matrix44 mat;
		
		Real ys = 1.0f / tan(fov / 2.0f);
		Real xs = ys / aspect;
				
		
		mat.m11 = xs;
		mat.m22 = ys;
		mat.m33 = zf / (zn - zf);
		mat.m34 = -1;
		mat.m43 = zn * zf / (zn - zf);

		return mat;
	}
	inline
		Matrix44 MatrixRotationRollPitchYaw(float Pitch, float Yaw, float Roll)
	{
		glm::quat q = glm::angleAxis(Pitch, glm::vec3(1, 0, 0)) * glm::angleAxis(Yaw, glm::vec3(0, 1, 0))* glm::angleAxis(Roll, glm::vec3(0, 0, 1));

		glm::mat4 m = glm::mat4_cast(q);

		return Matrix44(glm::value_ptr(m));

	}
	inline
		Quat Slerp(const Quat& q1, const Quat& q2, Real s)
	{
		glm::quat r = glm::slerp(glm::quat(q1.x, q1.y, q1.z, q1.w), glm::quat(q2.x, q2.y, q2.z, q2.w), s);

		return Quat(r.x, r.y, r.z, r.w);
	}
	inline
		Quat QuatRotationAxis(const Vector3& axis, Real rad)
	{
		glm::quat r = glm::angleAxis(rad, glm::make_vec3(axis.v));
		return Quat(r.x, r.y, r.z, r.w);

	}
	inline
		Quat QuatRotationMatrix(const Matrix44& m)
	{

		glm::quat r = glm::quat_cast(glm::make_mat4(m.m));


		return Quat(r.x, r.y, r.z, r.w);

	}
	inline
		Quat QuatRotationRollPitchYaw(float Pitch, float Yaw, float Roll)
	{

		glm::quat q = glm::angleAxis(Pitch, glm::vec3(1, 0, 0)) * glm::angleAxis(Yaw, glm::vec3(0, 1, 0))* glm::angleAxis(Roll, glm::vec3(0, 0, 1));

		return Quat(q.x, q.y, q.z, q.w);

	}
	inline
		void MatrixDecompose(const Matrix44& m, Vector3& s, Quat& r, Vector3& t)
	{
		Vector3 vx, vy, vz;

		vx = m.GetCol3(0);
		vy = m.GetCol3(1);
		vz = m.GetCol3(2);

		s.x = vx.Length();
		s.y = vy.Length();
		s.z = vz.Length();

		vx.Normalize();
		vy.Normalize();
		vz.Normalize();

		t = m.GetRow3(3);


		Matrix44 rot;
		rot.MakeIdentity();
		rot.SetCol3(0, vx);
		rot.SetCol3(1, vy);
		rot.SetCol3(2, vz);


		r = QuatRotationMatrix(rot);
		
	}

	inline
		Ray	UnProject(int x, int y, int vw, int vh, const Matrix44& worldTM, const Matrix44& ViewTM, const Matrix44& ProjTM)
	{
		Vector3 v;
		v.x = -( ( ( 2.0f * x ) / vw  ) - 1 ) / ProjTM(0,0);
		v.y = ( ( ( 2.0f * y ) / vh ) - 1 ) / ProjTM(1,1);
		v.z =  -1.0f;


		math::Matrix44 m = worldTM * ViewTM;
		m.Invert();

		Ray r;
		// Transform the screen space pick ray into 3D space
		r.d.x  = -(v.x*m(0,0) + v.y*m(1,0) + v.z*m(2,0));
		r.d.y  = -(v.x*m(0,1) + v.y*m(1,1) + v.z*m(2,1));
		r.d.z  = -(v.x*m(0,2) + v.y*m(1,2) + v.z*m(2,2));
		r.o.x = m(3,0);
		r.o.y = m(3,1);
		r.o.z = m(3,2);

		return r;
	}
}

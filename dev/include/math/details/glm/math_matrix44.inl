
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_major_storage.hpp>

namespace math
{
	

	inline
		const Matrix44& Matrix44::operator*=(const Matrix44& rhs)
	{

		glm::mat4x4 v = glm::make_mat4(m) * glm::make_mat4(rhs.m);
		memcpy(m, glm::value_ptr(v), sizeof(Real) * 16);

		return *this;
	}
	inline
		void Matrix44::Transpose()
	{
		glm::mat4x4 v = glm::transpose(glm::make_mat4(m));

		memcpy(m, glm::value_ptr(v), sizeof(Real) * 16);
	}
	inline
		void Matrix44::Invert()
	{
		glm::mat4x4 v = glm::inverse(glm::make_mat4(m));

		memcpy(m, glm::value_ptr(v), sizeof(Real) * 16);
	}
	inline
		Vector3 Matrix44::GetScale() const
	{
		return Vector3(GetCol3(0).Length(), GetCol3(1).Length(), GetCol3(2).Length());
	}
	inline
		void Matrix44::SetScale(const Vector3& s)
	{
		Vector3 vx(GetCol3(0)), vy(GetCol3(1)), vz(GetCol3(2));

		vx.Normalize();
		vx *= s.x;

		vy.Normalize();
		vy *= s.y;

		vz.Normalize();
		vz *= s.z;

		SetCol3(0, vx);
		SetCol3(1, vy);
		SetCol3(2, vz);

	}
	inline
		Matrix44 operator*(const Matrix44& lhs, const Matrix44& rhs)
	{
		glm::mat4 l = glm::make_mat4(lhs.m);
		glm::mat4 r = glm::make_mat4(rhs.m);

		const Real* p = glm::value_ptr(l * r);

		return Matrix44(p);

	}
}


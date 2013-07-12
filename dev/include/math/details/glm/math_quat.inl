#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace math
{
	inline
		void Quat::Invert()
	{
		glm::quat r(x, y, z, w);
		r = glm::inverse(r);

		x = r.x;
		y = r.y;
		z = r.z;
		w = r.w;
	}
	inline
		const Quat& Quat::operator*=(const Quat& rhs)
	{
		glm::quat q(x, y, z, w);
		
		q = q * glm::quat(rhs.x, rhs.y, rhs.z, rhs.w);
		
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}
	inline
		void Quat::Normalize()
	{

		glm::quat r(x, y, z, w);
		r = glm::normalize(r);

		x = r.x;
		y = r.y;
		z = r.z;
		w = r.w;
	}
}
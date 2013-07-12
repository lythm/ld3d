#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace math
{

	inline
		void Vector3::Normalize()
	{
		glm::vec3 r = glm::normalize(glm::make_vec3(v));

		x = r.x;
		y = r.y;
		z = r.z;
	}
}
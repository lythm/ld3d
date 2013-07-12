#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace math
{
	inline
		void Vector4::Normalize()
	{
		glm::vec4 r = glm::normalize(glm::make_vec4(v));
		x = r.x;
		y = r.y;
		z = r.z;
		w = r.w;
	}
}

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace math
{
	inline
		void Vector2::Normalize()
	{
		
		glm::vec2 r = glm::normalize(glm::make_vec2(v));

		x = r.x;
		y = r.y;
	}
}

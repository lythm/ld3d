#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace math
{
	inline	
		Plane::Plane(const Vector3& n, const Vector3& p)
	{
		
		normal = n;
		dist = -(n.x * p.x + n.y * p.y + p.z * p.z);
	}
	inline
		Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
	{
		glm::vec3 v1 = glm::make_vec3((p2 - p1).v);
		glm::vec3 v2 = glm::make_vec3((p3 - p1).v);

		v1 = glm::normalize(v1);
		v2 = glm::normalize(v2);


		glm::vec3 n = glm::cross(v1, v2);

		d = -glm::dot(n, glm::make_vec3(p1.v));

		normal.x = n.x;
		normal.y = n.y;
		normal.z = n.z;
	}
}

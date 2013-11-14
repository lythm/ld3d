#pragma once

namespace ld3d
{
	class Bound
	{
	public:

		Bound(void){}
		~Bound(void){}

		union
		{
			math::AABBox						aabb;
			math::Sphere						sphere;
		}
	};


}
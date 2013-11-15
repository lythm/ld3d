#pragma once

#include "core/Bound.h"

namespace ld3d
{
	class Bound_AABB : public Bound
	{
	public:
		Bound_AABB(void);
		virtual ~Bound_AABB(void);

		IntersectionResult										Intersect(BoundPtr other);
		IntersectionResult										Intersect(const math::Ray& r);


	private:
		math::AABBox											m_box;
		math::Matrix44											m_worldMatrix;
	};
}
#pragma once

#include "core/Bound.h"

namespace ld3d
{
	class Bound_Sphere : public Bound
	{
	public:
		Bound_Sphere(void);
		virtual ~Bound_Sphere(void);

		IntersectionResult										Intersect(BoundPtr other);
		IntersectionResult										Intersect(const math::Ray& r);

	private:
		math::Sphere											m_sphere;
		math::Matrix44											m_worldMatrix;

	};
}
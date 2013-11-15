#include "core_pch.h"
#include "core/Bound_Sphere.h"

namespace ld3d
{
	Bound_Sphere::Bound_Sphere(void) : Bound(bt_sphere)
	{
	}
	
	Bound_Sphere::~Bound_Sphere(void)
	{
	}
	IntersectionResult Bound_Sphere::Intersect(BoundPtr other)
	{
		return IntersectionResult();
	}
	IntersectionResult Bound_Sphere::Intersect(const math::Ray& r)
	{
		IntersectionResult ret;

		Real t = 0;
		
		if(math::intersect_none == math::RayIntersect(r, m_sphere, t))
		{
			ret.ret = IntersectionResult::no;
			return ret;
		}

		ret.ret = IntersectionResult::yes;
		ret.contact_point = r.GetPos(t);

		return ret;
	}
}

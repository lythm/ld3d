#include "core_pch.h"
#include "..\..\include\core\Bound_AABB.h"

namespace ld3d
{
	Bound_AABB::Bound_AABB(void) : Bound(bt_aabb)
	{
		m_worldMatrix.MakeIdentity();
	}


	Bound_AABB::~Bound_AABB(void)
	{
	}
	IntersectionResult Bound_AABB::Intersect(BoundPtr other)
	{
		return IntersectionResult();
	}
	IntersectionResult Bound_AABB::Intersect(const math::Ray& r)
	{
		Real t0 = 0;
		Real t1 = 0;

		IntersectionResult ret;

		if(math::intersect_none == math::RayIntersect(r, m_box, t0, t1))
		{
			ret.ret = IntersectionResult::no;
			return ret;
		}

		ret.ret = IntersectionResult::yes;
		ret.contact_point = r.GetPos(t0);
		return ret;
	}
}

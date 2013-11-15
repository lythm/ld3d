#pragma once

#include "core/IntersectionResult.h"

namespace ld3d
{
	class Bound
	{
	public:

		enum bound_type
		{
			bt_aabb,
			bt_sphere,
			bt_complex,
		};

		

		Bound(bound_type type)
		{
			m_type = type;
		}

		virtual ~Bound(void){}

		virtual IntersectionResult										Intersect(BoundPtr other)						= 0;
		virtual IntersectionResult										Intersect(const math::Ray& r)					= 0;



		bound_type														GetType() const
		{
			return m_type;
		}
	private:
		bound_type														m_type;
	};
}

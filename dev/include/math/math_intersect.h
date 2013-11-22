#ifndef __MATH_INTERSECTIONS_H__
#define __MATH_INTERSECTIONS_H__

#pragma once

#include <algorithm>

#ifndef __MATH_AABBOX_H__
#include <math/math_aabbox.h>
#endif

#ifndef __MATH_PLANE_H__
#include <math/math_plane.h>
#endif

#ifndef __MATH_RAY_H__
#include <math/math_ray.h>
#endif

#ifndef __MATH_ALG_H__
#include <math/math_alg.h>
#endif

namespace math
{
	// intersection test
	enum intersect_ret
	{
		intersect_front			= 0,
		intersect_back,
		intersect_none,
		intersect_inside,
		intersect_outside,
		intersect_intersect,
	};

	inline 
		void AABBoxFindOverlapp(const AABBox& b1, const AABBox& b2, AABBox& overlap)
	{
		Vector3 min_coord, max_coord;

		const Vector3& min1 = b1.GetMinCoord();
		const Vector3& min2 = b2.GetMinCoord();

		min_coord.x = std::max(min1.x, min2.x);
		min_coord.y = std::max(min1.y, min2.y);
		min_coord.z = std::max(min1.z, min2.z);

		const Vector3& max1 = b1.GetMaxCoord();
		const Vector3& max2 = b2.GetMaxCoord();

		max_coord.x = std::min(max1.x, max2.x);
		max_coord.y = std::min(max1.y, max2.y);
		max_coord.z = std::min(max1.z, max2.z);

		overlap.Make(min_coord, max_coord);

	}

	inline
		intersect_ret AABBoxIntersectAABBoxTest(const AABBox& lhs, const AABBox& rhs)
	{
		if( lhs.IsValid() == false || rhs.IsValid() == false)
			return intersect_none;

		const Vector3& lmax = lhs.GetMaxCoord();
		const Vector3& lmin = lhs.GetMinCoord();
		const Vector3& rmax = rhs.GetMaxCoord();
		const Vector3& rmin = rhs.GetMinCoord();

		if(lmax.x < rmin.x)
			return intersect_none;
		if(lmax.y < rmin.y)
			return intersect_none;
		if(lmax.z < rmin.z)
			return intersect_none;

		if(lmin.x > rmax.x)
			return intersect_none;
		if(lmin.y > rmax.y)
			return intersect_none;
		if(lmin.z > rmax.z)
			return intersect_none;

		return intersect_intersect;
	}

	inline
		intersect_ret AABBoxIntersectAABBox(const AABBox& lhs, const AABBox& rhs, AABBox& overlap)
	{
		intersect_ret ret = AABBoxIntersectAABBoxTest(lhs, rhs);
		
		if(ret != intersect_none)
		{
			AABBoxFindOverlapp(lhs, rhs, overlap);
		}

		return ret;
	}

	inline
		intersect_ret AABBoxIntersectSphere(const AABBox& box, const Sphere& sphere) 
	{
		Vector3 aabbcenter = box.GetCenter();
		Vector3 SepAxis = sphere.center - aabbcenter;
		Real Dist = SepAxis.Length();

		SepAxis.Normalize();
		
		if( SepAxis.x >= SepAxis.y && SepAxis.x >= SepAxis.z )
			SepAxis *= 1.0f / SepAxis.x;
		else if( SepAxis.y >= SepAxis.x && SepAxis.y >= SepAxis.z )
			SepAxis *= 1.0f / SepAxis.y;
		else
			SepAxis *= 1.0f / SepAxis.z;

		Vector3 extents = box.GetExtent();

		SepAxis.x *= extents.x / 2.0f;
		SepAxis.y *= extents.y / 2.0f;
		SepAxis.z *= extents.z / 2.0f;

		return Dist <= (sphere.radius + SepAxis.Length()) ? intersect_intersect : intersect_none;
	}

	

	inline
		intersect_ret RayIntersectPlane(const Ray& r, const Plane& p, Real& t)
	{
		Real dn = Dot(r.d, p.normal);
		if(dn == 0)
			return intersect_none;
		t = (p.dist - Dot(r.o , p.normal)) / dn;

		return dn < 0 ? intersect_front : intersect_back;
	}
	inline
		intersect_ret RayIntersect(const Ray& ray, const AABBox& box, Real& t0, Real& t1)
	{
		t0 = -MATH_REAL_INFINITY;
		t1 = MATH_REAL_INFINITY;

		const Vector3& minp = box.GetMinCoord();
		const Vector3& maxp = box.GetMaxCoord();
		const Vector3& p = ray.o;
		const Vector3& d = ray.d;

		for(int i = 0; i < 3; ++i)
		{
			if(abs(d[i]) < MATH_REAL_EPSILON)
			{
				if(p[i] < minp[i] || p[i] > maxp[i])
					return intersect_none;
			}

			Real tnear = (minp[i] - p[i]) / d[i];
			Real tfar = (maxp[i] - p[i]) / d[i];

			if(tnear > tfar)
			{
				std::swap(tnear, tfar);
			}
			if(tnear > t0)
			{
				t0 = tnear;
			}
			if(tfar < t1)
			{
				t1 = tfar;
			}
			if(t0 > t1)
			{
				return intersect_none;
			}
			if(t1 < 0)
			{
				return intersect_none;
			}
		}
			
		return intersect_intersect;
	}

	inline 
		intersect_ret RayIntersect(const Ray& ray, const Sphere& sphere, Real&	t0)
	{
		Real a, b, c, discrm;

		Vector3 pMinusC = ray.o - sphere.center;

		c = Dot(pMinusC, pMinusC) - sphere.radius * sphere.radius;
		// ray.m_ori in sphere
		if( c < 0)
			return intersect_none;


		a = Dot(ray.d, ray.d);
		b = 2 * Dot(ray.d, pMinusC);

		discrm = b * b - 4 * a * c;

		if(discrm > 0)
		{
			Real t;
			t = (-b - sqrt(discrm)) / (2  * a);
			if(t <= 0)
				return intersect_none;

			t0 = t;
			return intersect_intersect;
		}
		else if(discrm == 0)
		{
			Real t = -b / ( 2 * a);
			if(t <= 0)
				return intersect_none;
			t0 = t;
			return intersect_intersect;
		}
		
		return intersect_none;
	}
	inline
		intersect_ret RayIntersectPlaneTest(const Ray& r, const Plane& p)
	{
		Real dn = Dot(r.d, p.normal);
		if(dn == 0)
			return intersect_none;

		return dn < 0 ? intersect_front : intersect_back;
	}
	inline
		intersect_ret AABBoxIntersectPlaneTest(const AABBox& box, const Plane& plane)
	{
		Vector3 N(plane.a, plane.b, plane.c);
		Vector3 vmin, vmax;
		const Vector3& bmax = box.GetMaxCoord();
		const Vector3& bmin = box.GetMinCoord();

		for(int i = 0; i < 3; ++i)
		{
			if(N[i] >= 0)
			{
				vmin[i] = bmin[i];
				vmax[i] = bmax[i];
			}
			else
			{
				vmin[i] = bmax[i];
				vmax[i] = bmin[i];
			}
		}

		if((Dot(N, vmin) + plane.d) > 0)
			return intersect_outside;
		if((Dot(N, vmax) + plane.d) < 0)
			return intersect_inside;

		return intersect_intersect;
	}

}

#endif
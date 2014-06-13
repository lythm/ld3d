#ifndef __MATH_VIEWFRUSTUM_H__
#define __MATH_VIEWFRUSTUM_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

#include <math/math_plane.h>
#include <math/math_sphere.h>
#include <math/math_aabbox.h>
#include <math/math_vector3.h>
#include <math/math_matrix44.h>
#include <math/math_alg.h>

namespace math
{
	class ViewFrustum
	{
	public:
		enum
		{
			left_plane,
			right_plane,
			top_plane,
			bottom_plane,
			near_plane,
			far_plane,
			max_planes,
		};


		ViewFrustum(void);
		virtual ~ViewFrustum(void);

		void						Update(const math::Matrix44& view, const math::Matrix44& proj);
		bool						IntersectSphere(const math::Sphere& sphere) const;
		bool						IntersectBox(const math::AABBox& box) const;
		void						Transform(const math::Matrix44& t);
	private:
		math::Plane					m_planes[max_planes];
	};

	inline
		ViewFrustum::ViewFrustum(void)
	{
	}
	inline
		ViewFrustum::~ViewFrustum(void)
	{
	}
	inline
		void ViewFrustum::Update(const math::Matrix44& view, const math::Matrix44& proj)
	{
		math::Matrix44 M = view * proj;

		// left plane
		m_planes[left_plane].a		= M.m14 + M.m11;
		m_planes[left_plane].b		= M.m24 + M.m21;
		m_planes[left_plane].c		= M.m34 + M.m31;
		m_planes[left_plane].d		= M.m44 + M.m41;

		// right plane
		m_planes[right_plane].a		= M.m14 - M.m11;
		m_planes[right_plane].b		= M.m24 - M.m21;
		m_planes[right_plane].c		= M.m34 - M.m31;
		m_planes[right_plane].d		= M.m44 - M.m41;

		// top plane
		m_planes[top_plane].a		= M.m14 - M.m12;
		m_planes[top_plane].b		= M.m24 - M.m22;
		m_planes[top_plane].c		= M.m34 - M.m32;
		m_planes[top_plane].d		= M.m44 - M.m42;

		// bottom plane
		m_planes[bottom_plane].a		= M.m14 + M.m12;
		m_planes[bottom_plane].b		= M.m24 + M.m22;
		m_planes[bottom_plane].c		= M.m34 + M.m32;
		m_planes[bottom_plane].d		= M.m44 + M.m42;

		// near plane
		m_planes[near_plane].a		= M.m13;
		m_planes[near_plane].b		= M.m23;
		m_planes[near_plane].c		= M.m33;
		m_planes[near_plane].d		= M.m43;

		// far plane
		m_planes[far_plane].a		= M.m14 - M.m13;
		m_planes[far_plane].b		= M.m24 - M.m23;
		m_planes[far_plane].c		= M.m34 - M.m33;
		m_planes[far_plane].d		= M.m44 - M.m43;

		for(int i = 0; i < max_planes; ++i)
		{
			//float l = m_planes[i].normal.Length();
			m_planes[i].Normalize();

		}
	}
	inline
		bool ViewFrustum::IntersectBox(const math::AABBox& box) const
	{
		int vec_in_cnt;
		int plane_in_cnt = 0;

		math::Vector3 min = box.GetMinCoord();
		math::Vector3 max = box.GetMaxCoord();

		for( int p = 0; p < 6; p++ )
		{
			vec_in_cnt = 0;
			if( m_planes[p].a * min.x +
				m_planes[p].b * min.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * min.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * max.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * min.x +
				m_planes[p].b * max.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * min.x +
				m_planes[p].b * min.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * min.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * max.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * min.x +
				m_planes[p].b * max.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;

			if (vec_in_cnt == 0)
				return false;

			if (vec_in_cnt == 8)
				plane_in_cnt++;
		}

		return true;
		//return (plane_in_cnt == 6) ? 2 : 1;
	}
	inline
		bool ViewFrustum::IntersectSphere(const math::Sphere& sphere) const
	{
		float d = 0;

		for(int i = 0; i < 6; ++i) 
		{
			d = m_planes[i].PointDist(sphere.center);

			// if this distance is < -sphere.radius, we are outside
			if(d < -sphere.radius)
			{
				return false;
			}

			// else if the distance is between +- radius, then we intersect
			if((float)fabs(d) < sphere.radius)
				return true;
		}

		// inside
		return true;
	}
	inline
		void ViewFrustum::Transform(const math::Matrix44& t)
	{
		for(int i = 0; i < max_planes; ++i)
		{
			math::TransformPlane(m_planes[i], t);
		}
	}
}




#endif

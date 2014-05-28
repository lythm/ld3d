#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class Bound
		{
		public:

			Bound(const Coord& min_coord, const Coord& max_coord);
			Bound();

			~Bound(void);

			const Coord&			GetCenter() const;
			const Coord&			GetMaxCoord() const;
			const Coord&			GetMinCoord() const;
			const Coord&			GetExtent() const;

			void					SetMaxCoord(const Coord& max_coord);
			void					SetMinCoord(const Coord& min_coord);
			void					Make(const Coord& min_coord, const Coord& max_coord);

			void					Merge(const Bound& box);

			const Bound&			operator&=(const Bound& box);

			bool					IsValid() const;

			bool					Inside(const Coord& pt) const;

			Coord					PointNormal(const Coord& pt);
		private:
			void					UpdateValid();
			void					UpdateCenter();

			Coord					m_max;
			Coord					m_min;
			Coord					m_center;
			Coord					m_extent;
			bool					m_bValid;
		};

		inline
			bool Bound::Inside(const Coord& pt) const
		{
			return pt.x >= m_min.x 
				&& pt.y >= m_min.y
				&& pt.z >= m_min.z
				&& pt.x <= m_max.x
				&& pt.y <= m_max.y
				&& pt.z <= m_max.z;

		}

		inline
			Bound operator&(const Bound& lhs, const Bound& rhs)
		{
			Bound box = lhs;
			box &= rhs;
			return box;
		}

		inline
			Bound::Bound(void) : m_max(0, 0, 0), m_min(0, 0, 0)
		{
			UpdateValid();
			UpdateCenter();
		}
		inline
			Bound::Bound(const Coord& min_coord, const Coord& max_coord) : m_max(max_coord), m_min(min_coord)
		{
			UpdateValid();
			UpdateCenter();
		}
		inline
			Bound::~Bound(void)
		{
		}
		inline
			void Bound::UpdateCenter()
		{
			m_center = (m_max + m_min) * 0.5;
			m_extent = m_max - m_min;
		}
		inline
			const Coord& Bound::GetExtent() const
		{
			return m_extent;
		}

		inline
			const Coord& Bound::GetCenter() const
		{
			return m_center;
		}
		inline
			const Coord& Bound::GetMaxCoord() const
		{
			return m_max;
		}
		inline
			const Coord& Bound::GetMinCoord() const
		{
			return m_min;
		}
		inline
			void Bound::SetMaxCoord(const Coord& max_coord)
		{
			m_max = max_coord;
			UpdateValid();
			UpdateCenter();
		}
		inline
			void Bound::SetMinCoord(const Coord& min_coord)
		{
			m_min = min_coord;
			UpdateValid();
			UpdateCenter();
		}
		inline
			void Bound::Make(const Coord& min_coord, const Coord& max_coord)
		{
			m_max = max_coord;
			m_min = min_coord;
			UpdateValid();
			UpdateCenter();
		}
		inline
			void Bound::Merge(const Bound& box)
		{
			m_max.x = m_max.x < box.m_max.x ? box.m_max.x : m_max.x;
			m_max.y = m_max.y < box.m_max.y ? box.m_max.y : m_max.y;
			m_max.z = m_max.z < box.m_max.z ? box.m_max.z : m_max.z;

			m_min.x = m_min.x > box.m_min.x ? box.m_min.x : m_min.x;
			m_min.y = m_min.y > box.m_min.y ? box.m_min.y : m_min.y;
			m_min.z = m_min.z > box.m_min.z ? box.m_min.z : m_min.z;

			UpdateValid();
			UpdateCenter();
		}
		inline
			const Bound& Bound::operator&=(const Bound& box)
		{
			if(this == &box)
				return *this;
			Merge(box);
			return *this;
		}
		inline
			bool Bound::IsValid() const
		{	
			return m_bValid;
		}
		inline
			void Bound::UpdateValid()
		{
			if( m_max.x < m_min.x ||
				m_max.y < m_min.y ||
				m_max.z < m_min.z )

			{
				m_bValid = false;

				return;
			}

			m_bValid = true;
		}
	}
}
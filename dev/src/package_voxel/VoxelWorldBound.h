#pragma once

#include "core/Bound.h"

namespace ld3d
{
	class VoxelWorldBound : public Bound
	{
	public:
		VoxelWorldBound(void);
		virtual ~VoxelWorldBound(void);

		IntersectionResult										Intersect(BoundPtr other);
		IntersectionResult										Intersect(const math::Ray& r);

		void													SetWorld(VoxelWorldImplPtr pWorld);
	private:
		VoxelWorldImplPtr										m_pWorld;
	};
}

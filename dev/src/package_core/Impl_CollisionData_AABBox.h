#pragma once

#include "packages/core/CollisionData_AABBox.h"

namespace ld3d
{
	class Impl_CollisionData_AABBox : public CollisionData_AABBox
	{
	public:
		Impl_CollisionData_AABBox(GameObjectManagerPtr pManager);
		virtual ~Impl_CollisionData_AABBox(void);

		void													SetAABBox(const math::AABBox& box);
		void													SetHandler(std::function<void (CollisionDataPtr, const Contact&)> handler);
		bool													OnAttach();
		void													OnDetach();
		void													Update(float dt);
	private:
		CollisionDataPtr										m_pData;
		std::function<void (CollisionDataPtr, const Contact&)>	on_collide;
	};


}
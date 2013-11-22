#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class CollisionData_AABBox : public GameObjectComponent
	{
	public:


		virtual void													SetAABBox(const math::AABBox& box)											= 0;
		virtual void													SetHandler(std::function<void (CollisionDataPtr, const Contact&)> handler)	= 0;

	protected:

		CollisionData_AABBox(GameObjectManagerPtr pManager) : GameObjectComponent("CollisionData_AABBox", pManager){}

		virtual ~CollisionData_AABBox(void){}
	};

}

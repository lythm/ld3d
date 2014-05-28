#pragma once

#include "core/GameObjectComponent.h"
namespace ld3d
{

	class AABBoxRenderer: public GameObjectComponent
	{
	public:

		virtual void											SetAABBox(const math::AABBox& box)													= 0;
		
	protected:
		AABBoxRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("AABBoxRenderer", pManager){}
		virtual ~AABBoxRenderer(void){}


	};
}

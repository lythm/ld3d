#pragma once

#include "core/IntersectionResult.h"

namespace ld3d
{
	class _DLL_CLASS PhysicsManager
	{
	public:
		PhysicsManager(void);
		virtual ~PhysicsManager(void);


		bool										Initialize();
		void										Release();
		void										Update(float dt);

		void										AddCollider(CollisionDataPtr pData);
		void										RemoveCollider(CollisionDataPtr pData);

		void										AddCollidee(CollisionDataPtr pData);
		void										RemoveCollidee(CollisionDataPtr pData);


		IntersectionResult							RayIntersect(const math::Ray& r);

	private:
		void										Detect(CollisionDataPtr pCollider, CollisionDataPtr pCollidee);
		void										TestCollider(CollisionDataPtr pCollider);
	private:
		CollisionDataPtr							m_pColliderList;
		CollisionDataPtr							m_pCollideeList;
	};


}

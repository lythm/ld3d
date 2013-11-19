#pragma once

#include "core/Contact.h"

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


		Contact										RayIntersect(const math::Ray& r);

		
	private:
		void										UpdateCollision(float dt);
		void										UpdatePhysics(float dt);
		bool										Detect(CollisionDataPtr pCollider, CollisionDataPtr pCollidee);
		bool										TestCollider(CollisionDataPtr pCollider);

	private:
		Contact										_ray_intersect(const math::Ray& r, BoundPtr pBound);
		Contact										_ray_intersect(const math::Ray& r, const math::AABBox& aabb);
		Contact										_ray_intersect(const math::Ray& r, const math::Sphere& sphere);

		Contact										_aabb_intersect(BoundPtr box, BoundPtr pBound);
		Contact										_aabb_intersect(const math::AABBox& box1, const math::AABBox& box2);
		Contact										_aabb_intersect(const math::AABBox& box, const math::Sphere& s);

		Contact										_sphere_intersect(BoundPtr sphere, BoundPtr pBound);
		Contact										_sphere_intersect(const math::Sphere& s, const math::AABBox& box);
		Contact										_sphere_intersect(const math::Sphere& s1, const math::Sphere& s2);


	private:
		CollisionDataPtr							m_pColliderList;
		CollisionDataPtr							m_pCollideeList;
	};


}

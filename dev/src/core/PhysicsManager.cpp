#include "core_pch.h"
#include "core/PhysicsManager.h"

#include "core/CollisionData.h"
#include "core/Bound.h"

namespace ld3d
{
	PhysicsManager::PhysicsManager(void)
	{
	}


	PhysicsManager::~PhysicsManager(void)
	{
	}
	bool PhysicsManager::Initialize()
	{
		return true;
	}
	void PhysicsManager::Release()
	{
		CollisionDataPtr pData = m_pCollideeList;
		while(pData)
		{
			CollisionDataPtr pTmp = pData;
			pData = pData->Next();

			pTmp->Unlink();
		}

		pData = m_pColliderList;
		while(pData)
		{
			CollisionDataPtr pTmp = pData;
			pData = pData->Next();

			pTmp->Unlink();
		}
	}
	void PhysicsManager::Update(float dt)
	{
		UpdatePhysics(dt);
		UpdateCollision(dt);
	}
	void PhysicsManager::AddCollider(CollisionDataPtr pData)
	{
		if(pData->bound->type == Bound::bt_complex)
		{
			assert(0);
			return;
		}
		if(m_pColliderList == nullptr)
		{
			m_pColliderList = pData;
			return;
		}

		m_pColliderList->Insert(pData);

	}
	void PhysicsManager::RemoveCollider(CollisionDataPtr pData)
	{
		if(pData == nullptr)
		{
			return;
		}

		if(pData == m_pColliderList)
		{
			m_pColliderList = pData->Next();
		}
		pData->Unlink();
	}
	void PhysicsManager::AddCollidee(CollisionDataPtr pData)
	{
		if(m_pCollideeList == nullptr)
		{
			m_pCollideeList = pData;
			return;
		}

		m_pCollideeList->Insert(pData);
	}
	void PhysicsManager::RemoveCollidee(CollisionDataPtr pData)
	{
		if(pData == nullptr)
		{
			return;
		}

		if(pData == m_pCollideeList)
		{
			m_pCollideeList = pData->Next();
		}
		pData->Unlink();
	}
	bool PhysicsManager::Detect(CollisionDataPtr pCollider, CollisionDataPtr pCollidee)
	{
		Contact ret;

		switch(pCollider->bound->type)
		{
		case Bound::bt_aabb:
			ret = _aabb_intersect(pCollider->bound, pCollidee->bound);
			break;
		case Bound::bt_sphere:
			ret = _sphere_intersect(pCollider->bound, pCollidee->bound);
			break;
		case Bound::bt_complex:
		default:
			assert(0);
			break;
		}

		return ret.result == Contact::Yes;
	}
	bool PhysicsManager::TestCollider(CollisionDataPtr pCollider)
	{
		CollisionDataPtr pData = m_pCollideeList;
		while(pData)
		{
			if(Detect(pCollider, pData) == true)
			{
				if(pData->on_collide)
				{
					pData->on_collide();
				}
				return true;
			}

			pData = pData->Next();
		}

		return false;
	}
	Contact PhysicsManager::RayIntersect(const math::Ray& r)
	{
		Contact ret;
		ret.result = Contact::No;

		Real tnear = math::MATH_REAL_INFINITY;


		CollisionDataPtr pData = m_pCollideeList;
		while(pData)
		{
			Contact ret_tmp = _ray_intersect(r, pData->bound);

			if(ret_tmp.result == Contact::No)
			{
				pData = pData->Next();
				continue;
			}

			if(ret_tmp.result == Contact::Invalid)
			{
				pData = pData->Next();
				continue;
			}

			Real t = r.GetT(ret_tmp.enter_point);
			if(tnear > t)
			{
				tnear = t;
				ret = ret_tmp;
			}

			pData = pData->Next();
		}

		return ret;
	}
	void PhysicsManager::UpdateCollision(float dt)
	{
		CollisionDataPtr pData = m_pColliderList;

		uint32 try_count = 10;

		while(pData)
		{
			for(uint32 i = 0; i < try_count; ++i)
			{
				if(false == TestCollider(pData))
				{
					break;
				}
			}
			
			pData = pData->Next();
		}
	}
	void PhysicsManager::UpdatePhysics(float dt)
	{
	}
	Contact PhysicsManager::_ray_intersect(const math::Ray& r, const math::AABBox& aabb)
	{
		Real t0 = 0;
		Real t1 = 0;

		Contact ret;

		if(math::intersect_none == math::RayIntersect(r, aabb, t0, t1))
		{
			ret.result = Contact::No;
			return ret;
		}

		ret.result = Contact::Yes;
		ret.enter_point = r.GetPos(t0);
		return ret;

	}
	Contact PhysicsManager::_ray_intersect(const math::Ray& r, const math::Sphere& sphere)
	{
		Contact ret;

		Real t = 0;

		if(math::intersect_none == math::RayIntersect(r, sphere, t))
		{
			ret.result = Contact::No;
			return ret;
		}

		ret.result = Contact::Yes;
		ret.enter_point = r.GetPos(t);

		return ret;

	}
	Contact PhysicsManager::_ray_intersect(const math::Ray& r, BoundPtr pBound)
	{
		math::Ray new_r = r;

		math::Matrix44 invWorld = pBound->worldMatrix;
		invWorld.Invert();

		math::TransformRay(new_r, invWorld);

		Contact ret;
		switch(pBound->type)
		{
		case Bound::bt_aabb:
			{
				ret = _ray_intersect(new_r, ((Bound_AABB*)pBound.get())->aabb);

				Real t = new_r.GetT(ret.enter_point);

				ret.enter_point = r.GetPos(t);

				return ret;
			}
			break;
		case Bound::bt_sphere:
			{
				ret = _ray_intersect(new_r, ((Bound_Sphere*)pBound.get())->sphere);

				Real t = new_r.GetT(ret.enter_point);

				ret.enter_point = r.GetPos(t);

				return ret;
			}
			break;
		case Bound::bt_complex:
			{
				return ((Bound_Complex*)pBound.get())->RayIntersect(r);
			}
			break;
		default:
			assert(0);
			break;
		}

		return ret;
	}
	Contact	PhysicsManager::_aabb_intersect(BoundPtr box, BoundPtr pBound)
	{
		Contact ret;

		Bound_AABB* pBox = (Bound_AABB*)box.get();

		switch(pBound->type)
		{
		case Bound::bt_aabb:
			{
				Bound_AABB* pOther = (Bound_AABB*)pBound.get();
				ret = _aabb_intersect(pBox->aabb, pOther->aabb);

				return ret;

			}
			break;
		case Bound::bt_sphere:
			{
				Bound_Sphere* pOther = (Bound_Sphere*)pBound.get();
				ret = _aabb_intersect(pBox->aabb, pOther->sphere);
				return ret;
			}
			break;
		case Bound::bt_complex:
			{
				Bound_Complex* pOther = (Bound_Complex*)pBound.get();
				ret = pOther->Intersect(box);
				return ret;
			}
			break;
		default:
			assert(0);
			break;
		}

		return ret;
	}
	Contact PhysicsManager::_aabb_intersect(const math::AABBox& box1, const math::AABBox& box2)
	{
		Contact ret;

		math::AABBoxIntersectAABBox(box1, box2);

		return ret;
	}
	Contact PhysicsManager::_aabb_intersect(const math::AABBox& box, const math::Sphere& s)
	{
		Contact ret;


		return ret;
	}
	Contact PhysicsManager::_sphere_intersect(const math::Sphere& s, const math::AABBox& box)
	{
		Contact ret;


		return ret;
	}
	Contact PhysicsManager::_sphere_intersect(const math::Sphere& s1, const math::Sphere& s2)
	{
		Contact ret;


		return ret;
	}
	Contact PhysicsManager::_sphere_intersect(BoundPtr sphere, BoundPtr pBound)
	{
		Contact ret;

		Bound_Sphere* pSphere = (Bound_Sphere*)sphere.get();

		switch(pBound->type)
		{
		case Bound::bt_aabb:
			{
				Bound_AABB* pOther = (Bound_AABB*)pBound.get();
				ret = _sphere_intersect(pSphere->sphere, pOther->aabb);

				return ret;

			}
			break;
		case Bound::bt_sphere:
			{
				Bound_Sphere* pOther = (Bound_Sphere*)pBound.get();
				ret = _sphere_intersect(pSphere->sphere, pOther->sphere);
				return ret;
			}
			break;
		case Bound::bt_complex:
			{
				Bound_Complex* pOther = (Bound_Complex*)pBound.get();
				ret = pOther->Intersect(sphere);
				return ret;
			}
			break;
		default:
			assert(0);
			break;
		}

		return ret;
	}
}

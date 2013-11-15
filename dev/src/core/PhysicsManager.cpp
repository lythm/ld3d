#include "core_pch.h"
#include "core/PhysicsManager.h"

#include "core/Collidee.h"
#include "core/Collider.h"
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
		CollisionDataPtr pData = m_pColliderList;
		while(pData)
		{
			TestCollider(pData);

			pData = pData->Next();
		}
	}
	void PhysicsManager::AddCollider(CollisionDataPtr pData)
	{
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
	void PhysicsManager::Detect(CollisionDataPtr pCollider, CollisionDataPtr pCollidee)
	{
		pCollidee->bound->Intersect(pCollider->bound);
	}
	void PhysicsManager::TestCollider(CollisionDataPtr pCollider)
	{
		CollisionDataPtr pData = m_pCollideeList;
		while(pData)
		{
			Detect(pCollider, pData);

			pData = pData->Next();
		}
	}
	IntersectionResult PhysicsManager::RayIntersect(const math::Ray& r)
	{
		IntersectionResult ret;
		ret.ret = IntersectionResult::no;
		
		Real tnear = math::MATH_REAL_INFINITY;


		CollisionDataPtr pData = m_pCollideeList;
		while(pData)
		{
			IntersectionResult ret_tmp = pData->bound->Intersect(r);
			
			if(ret_tmp.ret == IntersectionResult::no)
			{
				pData = pData->Next();
				continue;
			}

			if(ret_tmp.ret == IntersectionResult::invalid)
			{
				pData = pData->Next();
				continue;
			}
						
			Real t = r.GetT(ret_tmp.contact_point);
			if(tnear > t)
			{
				tnear = t;
				ret = ret_tmp;
			}

			pData = pData->Next();
		}

		return ret;
	}
}

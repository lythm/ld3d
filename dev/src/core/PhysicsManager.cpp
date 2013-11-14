#include "core_pch.h"
#include "core/PhysicsManager.h"

#include "core/Collidee.h"
#include "core/Collider.h"

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
	}
	void PhysicsManager::Update(float dt)
	{
	}
	void PhysicsManager::AddCollider(ColliderPtr pCollider)
	{
		if(m_pColliderList == nullptr)
		{
			m_pColliderList = pCollider;
			return;
		}

		m_pColliderList->Insert(pCollider);

	}
	void PhysicsManager::RemoveCollider(ColliderPtr pCollider)
	{
		if(pCollider == nullptr)
		{
			return;
		}

		if(pCollider == m_pColliderList)
		{
			m_pColliderList = pCollider->Next();
		}
		pCollider->Unlink();
	}
	void PhysicsManager::AddCollidee(CollideePtr pCollidee)
	{
		if(m_pCollideeList == nullptr)
		{
			m_pCollideeList = pCollidee;
			return;
		}

		m_pCollideeList->Insert(pCollidee);
	}
	void PhysicsManager::RemoveCollidee(CollideePtr pCollidee)
	{
		if(pCollidee == nullptr)
		{
			return;
		}

		if(pCollidee == m_pCollideeList)
		{
			m_pCollideeList = pCollidee->Next();
		}
		pCollidee->Unlink();
	}
}

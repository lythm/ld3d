#include "core_ext_pch.h"
#include "Impl_CollisionData_AABBox.h"

namespace ld3d
{
	Impl_CollisionData_AABBox::Impl_CollisionData_AABBox(GameObjectManagerPtr pManager) : CollisionData_AABBox(pManager)
	{
		m_pData = m_pManager->alloc_object<CollisionData>();

		m_pData->bound = m_pManager->alloc_object<Bound_AABB>(math::AABBox());

		m_pData->enabled = true;
		m_pData->bound->type = Bound::bt_aabb;
	}


	Impl_CollisionData_AABBox::~Impl_CollisionData_AABBox(void)
	{
	}
	
	bool Impl_CollisionData_AABBox::OnAttach()
	{
		m_pData->bound->worldMatrix = m_pObject->GetWorldTransform();
		m_pManager->GetPhysicsManager()->AddCollider(m_pData);
		m_pData->on_collide = on_collide;
		return true;
	}
	void Impl_CollisionData_AABBox::OnDetach()
	{
		m_pManager->GetPhysicsManager()->RemoveCollider(m_pData);
		m_pData.reset();

	}
	void Impl_CollisionData_AABBox::SetAABBox(const math::AABBox& box)
	{
		((Bound_AABB*)m_pData->bound.get())->aabb = box;
	}
	void Impl_CollisionData_AABBox::Update(float dt)
	{
		m_pData->bound->worldMatrix = m_pObject->GetWorldTransform();
	}
	void Impl_CollisionData_AABBox::SetHandler(std::function<void (CollisionDataPtr, const Contact&)> handler)
	{
		on_collide = handler;
		m_pData->on_collide = on_collide;
	}
}

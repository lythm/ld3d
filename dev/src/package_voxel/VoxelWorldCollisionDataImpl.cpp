#include "voxel_pch.h"
#include "VoxelWorldCollisionDataImpl.h"
#include "VoxelWorldImpl.h"

namespace ld3d
{
	VoxelWorldCollisionDataImpl::VoxelWorldCollisionDataImpl(GameObjectManagerPtr pManager) : VoxelWorldCollisionData(pManager)
	{
		
	}


	VoxelWorldCollisionDataImpl::~VoxelWorldCollisionDataImpl(void)
	{
	}
	void VoxelWorldCollisionDataImpl::Update(float dt)
	{
	}

	bool VoxelWorldCollisionDataImpl::OnAttach()
	{

		m_pWorld			= std::dynamic_pointer_cast<VoxelWorldImpl>(m_pObject->GetComponent("VoxelWorld"));

		if(m_pWorld == nullptr)
		{
			return false;
		}

		m_pCD										= m_pManager->alloc_object<CollisionData>();
		std::shared_ptr<Bound_Complex> bound		= m_pManager->alloc_object<Bound_Complex>();

		bound->RayIntersect = std::bind(&VoxelWorldCollisionDataImpl::RayIntersect, this, std::placeholders::_1);
		bound->Intersect = std::bind(&VoxelWorldCollisionDataImpl::Intersect, this, std::placeholders::_1);
		m_pCD->bound = bound;

		m_pPhysicsManager	= m_pManager->GetPhysicsManager();
		
		m_pPhysicsManager->AddCollidee(m_pCD);
		return true;
	}
	void VoxelWorldCollisionDataImpl::OnDetach()
	{
		ClearPropertySet();

		m_pPhysicsManager->RemoveCollidee(m_pCD);
		m_pCD.reset();
		m_pPhysicsManager.reset();
	}
	Contact VoxelWorldCollisionDataImpl::RayIntersect(const math::Ray& r)
	{
		Contact ret;

		if(m_pWorld == nullptr)
		{
			return ret;
		}

		return m_pWorld->Intersect(r);
	}
	Contact	VoxelWorldCollisionDataImpl::Intersect(BoundPtr pBound)
	{
		Contact ret;

		if(m_pWorld == nullptr)
		{
			return ret;
		}
		
		return m_pWorld->Intersect(pBound);
	}
}

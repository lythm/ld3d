#include "voxel_pch.h"
#include "VoxelWorldCollisionDataImpl.h"
#include "VoxelWorldBound.h"
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

		m_pCD				= m_pManager->alloc_object<CollisionData>();
		m_pBound			= m_pManager->alloc_object<VoxelWorldBound>();

		m_pBound->SetWorld(m_pWorld);

		m_pCD->bound		= m_pBound;

		m_pPhysicsManager	= m_pManager->GetPhysicsManager();
		
		m_pPhysicsManager->AddCollidee(m_pCD);
		return true;
	}
	void VoxelWorldCollisionDataImpl::OnDetach()
	{
		ClearPropertySet();

		m_pPhysicsManager->RemoveCollidee(m_pCD);
		m_pCD.reset();
		m_pBound.reset();
		m_pPhysicsManager.reset();
	}
}

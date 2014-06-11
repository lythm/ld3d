#include "voxel_pch.h"
#include "VoxelWorldImpl2.h"

namespace ld3d
{
	VoxelWorldImpl2::VoxelWorldImpl2(GameObjectManagerPtr pManager) : VoxelWorld(pManager)
	{
		m_voxelSize				= 1;
		m_worldSizeX			= 10;
		m_worldSizeY			= 2;
		m_worldSizeZ			= 10;
		
		SetVersion(g_packageVersion);
	}


	VoxelWorldImpl2::~VoxelWorldImpl2(void)
	{
	}
	const int& VoxelWorldImpl2::GetWorldSizeX()
	{
		return m_worldSizeX;
	}
	void VoxelWorldImpl2::SetWorldSizeX(const int& x)
	{
		m_worldSizeX = x;
	}

	const int& VoxelWorldImpl2::GetWorldSizeY()
	{
		return m_worldSizeY;
	}
	void VoxelWorldImpl2::SetWorldSizeY(const int& y)
	{
		m_worldSizeY = y;
	}

	const int& VoxelWorldImpl2::GetWorldSizeZ()
	{
		return m_worldSizeZ;
	}
	void VoxelWorldImpl2::SetWorldSizeZ(const int& z)
	{
		m_worldSizeZ = z;
	}
	const int& VoxelWorldImpl2::GetVoxelSize()
	{
		return m_voxelSize;
	}
	void VoxelWorldImpl2::SetVoxelSize(const int& blockSize)
	{
		m_voxelSize = blockSize;
	}
	bool VoxelWorldImpl2::CreateWorld(const std::string& name)
	{
		if(m_pWorld == nullptr)
		{
			m_pWorld = m_pManager->alloc_object<voxel::World>();
		}

		return m_pWorld->Create(name, nullptr, m_pManager->GetAllocator());
	}
	void VoxelWorldImpl2::DestroyWorld()
	{
		if(m_pWorld == nullptr)
		{
			return;
		}

		m_pWorld->Destroy();
		m_pWorld = nullptr;

	}
	void VoxelWorldImpl2::Update(float dt)
	{
	}
	bool VoxelWorldImpl2::OnAttach()
	{
		RegisterProperty<int, VoxelWorldImpl2>(this,
				"Voxel Size",
				&VoxelWorldImpl2::GetVoxelSize,
				&VoxelWorldImpl2::SetVoxelSize);

		RegisterProperty<int, VoxelWorldImpl2>(this,
				"World Size X",
				&VoxelWorldImpl2::GetWorldSizeX,
				&VoxelWorldImpl2::SetWorldSizeX);

		RegisterProperty<int, VoxelWorldImpl2>(this,
				"World Size Y",
				&VoxelWorldImpl2::GetWorldSizeY,
				&VoxelWorldImpl2::SetWorldSizeY);

		RegisterProperty<int, VoxelWorldImpl2>(this,
				"World Size Z",
				&VoxelWorldImpl2::GetWorldSizeZ,
				&VoxelWorldImpl2::SetWorldSizeZ);


		
		return true;
	}
	void VoxelWorldImpl2::OnDetach()
	{
		ClearPropertySet();

		DestroyWorld();
	}
}

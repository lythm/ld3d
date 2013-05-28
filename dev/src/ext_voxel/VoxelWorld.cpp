#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorld.h"
#include "ext_voxel\VoxelBlock.h"

#include "VoxelPolygonizer.h"
#include "VoxelWorldGenerator.h"
#include "VoxelPool.h"

namespace ld3d
{
	VoxelWorld::VoxelWorld(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelWorld", pManager)
	{
		m_voxelSize				= 1;
		m_worldSizeX			= 10;
		m_worldSizeY			= 10;
		m_worldSizeZ			= 10;
		

		m_pPolygonizer = pManager->GetAllocator()->AllocObject<VoxelPolygonizer>();
	}


	VoxelWorld::~VoxelWorld(void)
	{
	}
	void VoxelWorld::Update(float dt)
	{

	}
	const Version& VoxelWorld::GetVersion() const
	{
		return g_packageVersion;
	}

	bool VoxelWorld::OnAttach()
	{

		m_pVoxelPool = m_pManager->GetAllocator()->AllocObject<VoxelPool>();
		if(m_pVoxelPool->Initialize(100000) == false)
		{
			return false;
		}
		PropertyManagerPtr pPM = boost::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelWorld");
		{
			pPM->RegisterProperty<int, VoxelWorld>(this,
				L"Voxel Size",
				&VoxelWorld::GetVoxelSize,
				&VoxelWorld::SetVoxelSize);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				L"World Size X",
				&VoxelWorld::GetWorldSizeX,
				&VoxelWorld::SetWorldSizeX);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				L"World Size Y",
				&VoxelWorld::GetWorldSizeY,
				&VoxelWorld::SetWorldSizeY);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				L"World Size Z",
				&VoxelWorld::GetWorldSizeZ,
				&VoxelWorld::SetWorldSizeZ);
		}
		pPM->End();


		m_pPolygonizer->Reset();

		RebuildWorld();

		return true;
	}
	void VoxelWorld::DestroyWorld()
	{
		for(size_t i = 0;i < m_voxels.size(); ++i)
		{
			m_pVoxelPool->Free(m_voxels[i]);
		}
		m_voxels.clear();
	}
	const int& VoxelWorld::GetVoxelSize()
	{
		return m_voxelSize;
	}
	void VoxelWorld::SetVoxelSize(const int& blockSize)
	{
		m_voxelSize = blockSize;
	}
	void VoxelWorld::OnDetach()
	{
		DestroyWorld();

		m_pVoxelPool->Release();
	}
	void VoxelWorld::AddBlock(Voxel* pVoxel)
	{

	}
	void VoxelWorld::RemoveBlock()
	{
	}
	const int& VoxelWorld::GetWorldSizeX()
	{
		return m_worldSizeX;
	}
	void VoxelWorld::SetWorldSizeX(const int& x)
	{
		DestroyWorld();
		m_worldSizeX = x;
		RebuildWorld();
	}

	const int& VoxelWorld::GetWorldSizeY()
	{
		return m_worldSizeY;
	}
	void VoxelWorld::SetWorldSizeY(const int& y)
	{
		DestroyWorld();
		m_worldSizeY = y;
		RebuildWorld();
	}

	const int& VoxelWorld::GetWorldSizeZ()
	{
		return m_worldSizeZ;
	}
	void VoxelWorld::SetWorldSizeZ(const int& z)
	{
		DestroyWorld();
		m_worldSizeZ = z;
		RebuildWorld();


	}
	void VoxelWorld::RebuildWorld()
	{
		m_pManager->Log(L"Rebuilding Voxel world...");
		DestroyWorld();

		Generate();

		m_pManager->Log(L"Voxel world rebuilt.");
		
	}
	
	void VoxelWorld::Generate()
	{
		m_voxels = VoxelWorldGenerator::Generate(m_pVoxelPool, m_worldSizeX, m_worldSizeY, m_worldSizeZ);

		for(size_t i = 0; i < m_voxels.size(); ++i)
		{
			AddBlock(m_voxels[i]);
		}

		Polygonize();

	}
	void VoxelWorld::FrustumCull(BaseCameraPtr pCamera)
	{

	}
	void VoxelWorld::Polygonize()
	{
		m_pPolygonizer->Process(boost::dynamic_pointer_cast<VoxelWorld>(shared_from_this()));

		// build octree from polygons
		// 
	}
}


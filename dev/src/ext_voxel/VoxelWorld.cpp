#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorld.h"
#include "VoxelWorldChunk.h"

#include "VoxelPolygonizer.h"
#include "VoxelWorldGenerator.h"
#include "VoxelPool.h"
#include "VoxelWorldDataSet.h"

namespace ld3d
{
	VoxelWorld::VoxelWorld(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelWorld", pManager)
	{
		m_voxelSize				= 1;
		m_worldSizeX			= 10;
		m_worldSizeY			= 2;
		m_worldSizeZ			= 10;
		

		m_pPolygonizer = pManager->GetAllocator()->AllocObject<VoxelPolygonizer>();
	}


	VoxelWorld::~VoxelWorld(void)
	{
	}
	void VoxelWorld::Update(float dt)
	{
		m_pDataSet->UpdateMesh();
	}
	const Version& VoxelWorld::GetVersion() const
	{
		return g_packageVersion;
	}

	bool VoxelWorld::OnAttach()
	{

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
		if(m_pDataSet)
		{
			m_pDataSet->Release();
			m_pDataSet.reset();
		}
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

		int tick = GetTickCount();

		DestroyWorld();

		Generate();

		tick = GetTickCount() - tick;
		wchar_t szBuffer[512];

		swprintf(szBuffer, L"Voxel world rebuilt.(%d triangles in %.4fs)", m_pDataSet->GetFaceCount() * 2, float(tick) / 1000.0f);

		m_pManager->Log(szBuffer);
		
	}
	
	void VoxelWorld::Generate()
	{
		m_pDataSet = VoxelWorldGenerator::Generate(m_worldSizeX, m_worldSizeY, m_worldSizeZ);
		Polygonize();
		m_pDataSet->UpdateMesh();
	}
	VoxelWorldChunk* VoxelWorld::FrustumCull(BaseCameraPtr pCamera)
	{
		const ViewFrustum& vf = pCamera->GetViewFrustum();


		return m_pDataSet->FrustumCull(vf);
	}
	void VoxelWorld::Polygonize()
	{
		m_pPolygonizer->Process(boost::dynamic_pointer_cast<VoxelWorld>(shared_from_this()));

		// build octree from polygons
		// 
	}
	VoxelWorldDataSetPtr VoxelWorld::GetDataSet()
	{
		return m_pDataSet;
	}
	
}


#include "voxel_pch.h"
#include "ext_voxel/VoxelWorld.h"
#include "VoxelWorldChunk.h"
#include "VoxelWorldDataSet.h"

namespace ld3d
{
	VoxelWorld::VoxelWorld(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelWorld", pManager)
	{
		m_voxelSize				= 1;
		m_worldSizeX			= 10;
		m_worldSizeY			= 2;
		m_worldSizeZ			= 10;
		
		SetVersion(g_packageVersion);
	}


	VoxelWorld::~VoxelWorld(void)
	{
	}
	void VoxelWorld::Update(float dt)
	{
		if(m_pDataSet)
		{
			m_pDataSet->UpdateMesh();
		}
	}
	
	bool VoxelWorld::OnAttach()
	{

		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));

		pPM->Begin("VoxelWorld");
		{
			pPM->RegisterProperty<int, VoxelWorld>(this,
				"Voxel Size",
				&VoxelWorld::GetVoxelSize,
				&VoxelWorld::SetVoxelSize);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				"World Size X",
				&VoxelWorld::GetWorldSizeX,
				&VoxelWorld::SetWorldSizeX);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				"World Size Y",
				&VoxelWorld::GetWorldSizeY,
				&VoxelWorld::SetWorldSizeY);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				"World Size Z",
				&VoxelWorld::GetWorldSizeZ,
				&VoxelWorld::SetWorldSizeZ);

		}
		pPM->End();


		return true;
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
		if(m_pDataSet != nullptr)
		{
			m_pDataSet->Release();
			m_pDataSet.reset();
		}
	}
	const int& VoxelWorld::GetWorldSizeX()
	{
		return m_worldSizeX;
	}
	void VoxelWorld::SetWorldSizeX(const int& x)
	{
		m_worldSizeX = x;
	}

	const int& VoxelWorld::GetWorldSizeY()
	{
		return m_worldSizeY;
	}
	void VoxelWorld::SetWorldSizeY(const int& y)
	{
		m_worldSizeY = y;
	}

	const int& VoxelWorld::GetWorldSizeZ()
	{
		return m_worldSizeZ;
	}
	void VoxelWorld::SetWorldSizeZ(const int& z)
	{
		m_worldSizeZ = z;
	}
	
	VoxelWorldChunk* VoxelWorld::FrustumCull(BaseCameraPtr pCamera)
	{
		if(m_pDataSet == nullptr)
		{
			return nullptr;
		}
		const ViewFrustum& vf = pCamera->GetViewFrustum();

		return m_pDataSet->FrustumCull(vf);
	}
	
	VoxelWorldDataSetPtr VoxelWorld::GetDataSet()
	{
		return m_pDataSet;
	}

	bool VoxelWorld::OnSerialize(DataStream* pStream)
	{
		pStream->WriteInt32(m_worldSizeX);
		pStream->WriteInt32(m_worldSizeY);
		pStream->WriteInt32(m_worldSizeZ);
		pStream->WriteInt32(m_voxelSize);

		if(m_pDataSet == nullptr)
		{
			pStream->WriteInt32(0);
			return true;
		}

		return m_pDataSet->Serialize(pStream);
	}
	bool VoxelWorld::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != GetVersion())
		{
			return false;
		}

		m_worldSizeX = pStream->ReadInt32();
		m_worldSizeY = pStream->ReadInt32();
		m_worldSizeZ = pStream->ReadInt32();
		m_voxelSize = pStream->ReadInt32();

		if(m_pDataSet != nullptr)
		{
			m_pDataSet->Release();
		}
		m_pDataSet = m_pManager->alloc_object<VoxelWorldDataSet>();

		m_pDataSet->Initialize(m_worldSizeX, m_worldSizeY, m_worldSizeZ);
		
		return m_pDataSet->UnSerialize(pStream);
	}
	void VoxelWorld::SetDataSet(VoxelWorldDataSetPtr pDataSet)
	{
		if(m_pDataSet != nullptr)
		{
			m_pDataSet->Release();
			m_pDataSet.reset();
		}
		m_pDataSet = pDataSet;
	}
}


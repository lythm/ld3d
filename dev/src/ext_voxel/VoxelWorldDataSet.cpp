#include "voxel_pch.h"
#include "VoxelWorldDataSet.h"

#include "VoxelWorldChunk.h"
#include "VoxelPool.h"
#include "VoxelWorldRegion.h"


namespace ld3d
{
	VoxelWorldDataSet::VoxelWorldDataSet(void)
	{
	}


	VoxelWorldDataSet::~VoxelWorldDataSet(void)
	{
	}
	bool VoxelWorldDataSet::Initialize(float voxelSize)
	{
		m_pRegion = new VoxelWorldRegion;
		if(m_pRegion->Initialize() == false)
		{
			return false;
		}
		return true;
	}
	void VoxelWorldDataSet::Release()
	{
		if(m_pRegion)
		{
			m_pRegion->Release();
			delete m_pRegion;
			m_pRegion = nullptr;
		}
	}
	void VoxelWorldDataSet::Update()
	{
	}
	uint8 VoxelWorldDataSet::GetVoxelType(uint32 x, uint32 y, uint32 z)
	{
		return m_pRegion->GetBlock(x, y, z);
	}
	bool VoxelWorldDataSet::Exist(uint32 x, uint32 y, uint32 z)
	{
		return m_pRegion->Empty(x, y, z) == false;
	}
	bool VoxelWorldDataSet::AddVoxel(uint8 type, uint32 x, uint32 y, uint32 z)
	{
		return m_pRegion->AddBlock(type, x, y, z);
	}
	void VoxelWorldDataSet::RemoveVoxel(uint32 x, uint32 y, uint32 z)
	{
		m_pRegion->RemoveBlock(x, y, z);
	}
	
	VoxelWorldChunk* VoxelWorldDataSet::FrustumCull(const ViewFrustum& vf)
	{
		m_pRegion->FrustumCull(vf);

		return m_pRegion->GetRenderList();
	}
	void VoxelWorldDataSet::UpdateMesh()
	{
		m_pRegion->UpdateMesh();
	}
	uint32 VoxelWorldDataSet::GetFaceCount()
	{
		return m_pRegion->GetFaceCount();
	}

}

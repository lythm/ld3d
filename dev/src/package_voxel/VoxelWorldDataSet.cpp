#include "voxel_pch.h"
#include "VoxelWorldDataSet.h"

#include "VoxelWorldChunk.h"
#include "VoxelPool.h"
#include "VoxelWorldRegion.h"


namespace ld3d
{
	VoxelWorldDataSet::VoxelWorldDataSet(void)
	{
		m_worldSizeX			= 0;
		m_worldSizeY			= 0;
		m_worldSizeZ			= 0;

		m_pRegion = nullptr;
	}


	VoxelWorldDataSet::~VoxelWorldDataSet(void)
	{
	}
	bool VoxelWorldDataSet::Initialize(int sx, int sy, int sz, float voxelSize)
	{
		m_worldSizeX = sx;
		m_worldSizeY = sy;
		m_worldSizeZ = sz;

		m_pRegion = new VoxelWorldRegion;
		if(m_pRegion->Initialize(sx, sy, sz) == false)
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
	void VoxelWorldDataSet::ConvertVoxel(uint8 t, uint32 x, uint32 y, uint32 z)
	{
		m_pRegion->ConvertBlock(t, x, y, z);
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
		if(m_pRegion == nullptr)
		{
			return nullptr;
		}
		m_pRegion->FrustumCull(vf);

		return m_pRegion->GetRenderList();
	}
	void VoxelWorldDataSet::UpdateMesh()
	{
		if(m_pRegion != nullptr)
		{
			m_pRegion->UpdateMesh();
		}
	}
	uint32 VoxelWorldDataSet::GetFaceCount()
	{
		return m_pRegion ? m_pRegion->GetFaceCount() : 0;
	}

	bool VoxelWorldDataSet::Serialize(DataStream* pStream)
	{
		pStream->WriteInt32(1);
		VoxelWorldChunk** pMap = m_pRegion->GetChunkMap();

		uint64 chunk_count_pos = pStream->Pos();
		pStream->WriteInt32(0);

		uint32 chunk_count = 0;

		for(uint32 i = 0; i < VOXEL_WORLD_CHUNK_MAP_SIZE; ++i)
		{
			VoxelWorldChunk* pChunk = pMap[i];

			while(pChunk)
			{
				if(pChunk->GetBlockCount() != 0)
				{
					pStream->WriteInt32(pChunk->GetKey());
					pStream->Write(pChunk->GetBlockData(), sizeof(uint8) * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);
					++chunk_count;
				}
				pChunk = pChunk->GetMapNext();
			}
		}

		uint64 pos = pStream->Pos();
		pStream->Seek(chunk_count_pos);
		pStream->WriteInt32(chunk_count);
		pStream->Seek(pos);

		return true;
	}
	bool VoxelWorldDataSet::UnSerialize(DataStream* pStream)
	{
		uint32 region_count = pStream->ReadInt32();

		if(region_count == 0)
		{
			return true;
		}

		uint32 chunk_count = pStream->ReadInt32();

		for(uint32 i = 0; i < chunk_count; ++i)
		{
			uint32 key = pStream->ReadInt32();
			uint8 data[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE];
			pStream->Read(data, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			m_pRegion->AddChunk(key, data);
		}

		m_pRegion->UpdateMesh();
		return true;
	}
	const int& VoxelWorldDataSet::GetWorldSizeY()
	{
		return m_worldSizeY;
	}
	const int& VoxelWorldDataSet::GetWorldSizeX()
	{
		return m_worldSizeX;
	}
	const int& VoxelWorldDataSet::GetWorldSizeZ()
	{
		return m_worldSizeZ;
	}
	IntersectionResult VoxelWorldDataSet::Intersect(const math::Ray& r)
	{
		return m_pRegion->Intersect(r);
	}
}

#pragma once

namespace ld3d
{
	class VoxelWorldMesh;
	class VoxelWorldRegion;
	class VoxelWorldChunk
	{
	public:
		VoxelWorldChunk();
		virtual ~VoxelWorldChunk();


		bool												Init(uint32 key, VoxelWorldRegion* pRegion);
		void												Release();

		void												Reset();

		void												SetMapNext(VoxelWorldChunk* pNext);
		VoxelWorldChunk*									GetMapNext();
		
		void												SetDirtyListNext(VoxelWorldChunk* pNext);
		VoxelWorldChunk*									GetDirtyListNext();

		void												SetRenderListNext(VoxelWorldChunk* pNext);
		VoxelWorldChunk*									GetRenderListNext();
		
		uint32												GetKey();

		uint8*												GetBlockData();
		void												Load(uint32 key, uint8* data);
		

		uint8												GetBlock(uint32 index);
		void												SetBlock(uint32 index, uint8 value);

		void												SetDirty(bool dirty);
		bool												IsDirty();

		void												SetInOctTree(bool value);
		bool												IsInOctTree();

		math::Vector3										GetChunkCoord();

		math::Vector3										IndexToLocal(uint32 index);
		math::Vector3										IndexToGlobal(uint32 index);

		// non-empty block count
		uint32												GetBlockCount();
		void												UpdateMesh();

		VoxelWorldRegion*									GetRegion();

		VoxelWorldMesh*										GetMesh();

		bool												RayPick(const math::Ray& r, Real& t);
	private:
		//bool												_ray_pick(int lvl, const math::Ray& r, 
	private:

		VoxelWorldChunk*									m_pMapNext;
		VoxelWorldChunk*									m_pDirtyListNext;
		VoxelWorldChunk*									m_pRenderListNext;

		uint32												m_key;

		bool												m_dirty;
		bool												m_inOctTree;

		uint32												m_blockCount;
		uint8												m_pData[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE];

		VoxelWorldRegion*									m_pRegion;

		VoxelWorldMesh*										m_pMesh;
	};
}

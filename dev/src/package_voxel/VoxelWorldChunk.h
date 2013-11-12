#pragma once

namespace ld3d
{
	struct VoxelVertex
	{
		math::Vector3										pos;
		math::Vector3										normal;
		uint32												clr;
	};
	class VoxelWorldChunk
	{
	public:
		VoxelWorldChunk();
		virtual ~VoxelWorldChunk();


		void												Init(uint32 key);
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


		////////////////////////////////

		VoxelVertex*										vertex_buffer;
		int													vertex_count;

	
		///////////////////////////////////

	private:
		VoxelWorldChunk*									m_pMapNext;
		VoxelWorldChunk*									m_pDirtyListNext;
		VoxelWorldChunk*									m_pRenderListNext;

		uint32												m_key;

		bool												m_dirty;
		bool												m_inOctTree;

		uint32												m_blockCount;
		uint8												m_pData[VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE];
	};
}

#include "voxel_pch.h"
#include "VoxelWorldOctTree.h"
#include "VoxelWorldChunk.h"

namespace ld3d
{
	VoxelWorldOctTree::VoxelWorldOctTree(void)
	{
		m_pChunk				= nullptr;

		for(int i = 0; i < 8; ++i)
		{
			m_pChildren[i] = VoxelWorldOctTreePtr();
		}
	}

	VoxelWorldOctTree::~VoxelWorldOctTree(void)
	{
		for(int i = 0; i < 8; ++i)
		{
			m_pChildren[i].reset();
		}
		m_pChunk = nullptr;
	}
	const math::AABBox& VoxelWorldOctTree::GetBound() const
	{
		return m_bbox;
	}
	void VoxelWorldOctTree::SetBound(const math::AABBox& bound)
	{
		m_bbox = bound;
	}

	void VoxelWorldOctTree::SetChild(int iChild, VoxelWorldOctTreePtr pChild)
	{
		m_pChildren[iChild] = pChild;
	}
	VoxelWorldOctTreePtr VoxelWorldOctTree::GetChild(int iChild)
	{
		return m_pChildren[iChild];
	}

	bool VoxelWorldOctTree::IsLeaf() const
	{
		return m_pChunk != nullptr;
	}

	bool VoxelWorldOctTree::AddChunk(VoxelWorldChunk* pChunk)
	{
		if(pChunk == nullptr)
		{
			return false;
		}

		return _add_chunk(pChunk);
	}
	bool VoxelWorldOctTree::_add_chunk(VoxelWorldChunk* pChunk)
	{
		math::AABBox bound;

		math::Vector3 coord = pChunk->chunk_coord();
		bound.Make(coord, math::Vector3(
			coord.x + VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE,
			coord.y + VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE,
			coord.z + VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE));


		if(m_bbox.Inside(bound.GetCenter()) == false)
		{
			return false;
		}

		int len = int(m_bbox.GetMaxCoord().x - m_bbox.GetMinCoord().x);
		if(len == VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_BLOCK_SIZE)
		{
			m_pChunk = pChunk;
			return true;
		}

		math::AABBox sub[8];

		SubDivideBound(m_bbox, sub);

		for(int i = 0; i < 8; ++i)
		{
			if(sub[i].Inside(bound.GetCenter()))
			{
				if(m_pChildren[i] == nullptr)
				{
					m_pChildren[i] = VoxelWorldOctTreePtr(new VoxelWorldOctTree);
					m_pChildren[i]->SetBound(sub[i]);
				}
				return m_pChildren[i]->_add_chunk(pChunk);
			}
		}

		return false;
	}

	bool VoxelWorldOctTree::SubDivideBound(const math::AABBox& bound, math::AABBox Bounds[8])
	{
		/*
		z
		-|-x     
		0 - (-x, +y, +z)
		1 - (+x, +y, +z)
		2 - (-x, +y, -z)
		3 - (+x, +y, -z)

		4 - (-x, -y, +z)
		5 - (+x, -y, +z)
		6 - (-x, -y, -z)
		7 - (+x, -y, -z)
		*/

		if(bound.IsValid() == false)
			return false;

		const math::Vector3& center = bound.GetCenter();
		const math::Vector3& max_coord = bound.GetMaxCoord();
		const math::Vector3& min_coord = bound.GetMinCoord();


		Bounds[0].Make(math::Vector3(min_coord.x, center.y, center.z), math::Vector3(center.x, max_coord.y, max_coord.z));
		Bounds[1].Make(math::Vector3(center.x, center.y, center.z), math::Vector3(max_coord.x, max_coord.y, max_coord.z));
		Bounds[2].Make(math::Vector3(min_coord.x, center.y, min_coord.z), math::Vector3(center.x, max_coord.y, center.z));
		Bounds[3].Make(math::Vector3(center.x, center.y, min_coord.z), math::Vector3(max_coord.x, max_coord.y, center.z));

		Bounds[4].Make(math::Vector3(min_coord.x, min_coord.y, center.z), math::Vector3(center.x, center.y, max_coord.z));
		Bounds[5].Make(math::Vector3(center.x, min_coord.y, center.z), math::Vector3(max_coord.x, center.y, max_coord.z));
		Bounds[6].Make(math::Vector3(min_coord.x, min_coord.y, min_coord.z), math::Vector3(center.x, center.y, center.z));
		Bounds[7].Make(math::Vector3(center.x, min_coord.y, min_coord.z),math::Vector3(max_coord.x, center.y, center.z));

		return true;
	}
	void VoxelWorldOctTree::FrustumCull(const ViewFrustum& vf, boost::function<void (VoxelWorldChunk*)> op)
	{
		if(vf.IntersectBox(m_bbox) == false)
		{
			return;
		}
		if(IsLeaf())
		{
			op(m_pChunk);
			return;
		}
		

		for(size_t i = 0; i < 8; ++i)
		{
			if(m_pChildren[i] == nullptr)
			{
				continue;
			}
			m_pChildren[i]->FrustumCull(vf, op);
		}

	}
}

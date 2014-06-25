#include "voxel_pch.h"
#include "voxel_Octree.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_PoolManager.h"

namespace ld3d
{
	namespace voxel
	{
		Octree::Octree(const Coord& region_origin)
		{
			m_regionOrigin			= region_origin;
			m_pChunk				= nullptr;
			m_chunkCount			= 0;
			for(int i = 0; i < 8; ++i)
			{
				m_pChildren[i] = OctreePtr();
			}
		}

		Octree::~Octree(void)
		{
			for(int i = 0; i < 8; ++i)
			{
				m_pChildren[i].reset();
			}
			m_pChunk = nullptr;
		}
		const math::AABBox& Octree::GetBound() const
		{
			return m_bbox;
		}
		void Octree::SetBound(const math::AABBox& bound)
		{
			m_bbox = bound;
		}

		void Octree::SetChild(int iChild, OctreePtr pChild)
		{
			m_pChildren[iChild] = pChild;
		}
		OctreePtr Octree::GetChild(int iChild)
		{
			return m_pChildren[iChild];
		}

		bool Octree::IsLeaf() const
		{
			return m_pChunk != nullptr;
		}

		bool Octree::AddChunk(ChunkPtr pChunk)
		{
			if(pChunk == nullptr)
			{
				return false;
			}

			bool ret = _add_chunk(pChunk);
			if(ret == true)
			{
				++m_chunkCount;
			}
			return ret;
		}
		bool Octree::RemoveChunk(ChunkPtr pChunk)
		{
			bool ret = _remove_chunk(pChunk);
			if(ret == true)
			{
				--m_chunkCount;
			}
			return ret;
		}
		bool Octree::_remove_chunk(ChunkPtr pChunk)
		{
			math::AABBox bound;

			math::Vector3 coord = pChunk->GetKey().ToChunkOrigin().ToVector3() - m_regionOrigin.ToVector3();
			bound.Make(coord, math::Vector3(
				coord.x + CHUNK_SIZE * BLOCK_SIZE,
				coord.y + CHUNK_SIZE * BLOCK_SIZE,
				coord.z + CHUNK_SIZE * BLOCK_SIZE));


			if(m_bbox.Inside(bound.GetCenter()) == false)
			{
				return false;
			}

			int len = int(m_bbox.GetMaxCoord().x - m_bbox.GetMinCoord().x);
			if(len == CHUNK_SIZE * BLOCK_SIZE)
			{
				if(m_pChunk == nullptr)
				{
					return false;
				}
				m_pChunk = nullptr;
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
						return false;
					}
					return m_pChildren[i]->_remove_chunk(pChunk);
				}
			}

			return false;
		}
		bool Octree::_add_chunk(ChunkPtr pChunk)
		{
			math::AABBox bound;

			math::Vector3 coord = pChunk->GetKey().ToChunkOrigin().ToVector3() - m_regionOrigin.ToVector3();
			bound.Make(coord, math::Vector3(
				coord.x + CHUNK_SIZE * BLOCK_SIZE,
				coord.y + CHUNK_SIZE * BLOCK_SIZE,
				coord.z + CHUNK_SIZE * BLOCK_SIZE));


			if(m_bbox.Inside(bound.GetCenter()) == false)
			{
				return false;
			}

			int len = int(m_bbox.GetMaxCoord().x - m_bbox.GetMinCoord().x);
			if(len == CHUNK_SIZE * BLOCK_SIZE)
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
						m_pChildren[i] = pool_manager()->AllocOctTree(m_regionOrigin);
						m_pChildren[i]->SetBound(sub[i]);
					}
					return m_pChildren[i]->_add_chunk(pChunk);
				}
			}

			return false;
		}

		bool Octree::SubDivideBound(const math::AABBox& bound, math::AABBox Bounds[8])
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
		void Octree::FrustumCull(const math::ViewFrustum& vf, std::function<void (ChunkMeshPtr)> op)
		{
			if(vf.IntersectBox(m_bbox) == false)
			{
				return;
			}
			if(IsLeaf())
			{
				if(m_pChunk == nullptr)
				{
					return;
				}
				ChunkMeshPtr pMesh = m_pChunk->GetMesh();

				if(pMesh)
				{
					op(pMesh);
				}
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
		bool Octree::RayPick(const math::Ray& r, Real& t)
		{
			Real t0, t1;
			if(math::RayIntersect(r, m_bbox, t0, t1) == math::intersect_none)
			{
				return false;
			}

			t = t0;

			if(IsLeaf())
			{
				return m_pChunk != nullptr;
			}

			Real near_t = math::MATH_REAL_INFINITY;
			bool found = false;
			for(size_t i = 0; i < 8; ++i)
			{
				if(m_pChildren[i] == nullptr)
				{
					continue;
				}

				if(false == m_pChildren[i]->RayPick(r, t))
				{
					continue;
				}

				found = true;
				if(near_t > t)
				{
					near_t = t;
				}
			}

			t = near_t;

			return found;
		}
		const Coord& Octree::GetRegionOrigin() const
		{
			return m_regionOrigin;
		}
		int32 Octree::GetChunkCount() const
		{
			return m_chunkCount;
		}
	}
}
#include "voxel_pch.h"
#include "voxel_OctreeManager.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_VoxelUtils.h"
#include "voxel_Octree.h"
#include "voxel_PoolManager.h"
#include "voxel/voxel_ChunkMesh.h"

namespace ld3d
{
	namespace voxel
	{
		OctreeManager::OctreeManager(void)
		{
			m_faceCount = 0;
		}


		OctreeManager::~OctreeManager(void)
		{
			Clear();
		}
		void OctreeManager::Clear()
		{
			m_octrees.clear();
		}
		void OctreeManager::Update()
		{
		}
		OctreePtr OctreeManager::FindOctree(const Coord& region_origin)
		{
			for(auto root : m_octrees)
			{
				if(root->GetRegionOrigin() == region_origin)
				{
					return root;
				}
			}
			return nullptr;

		}
		void OctreeManager::AddChunk(ChunkPtr pChunk)
		{
			ChunkMeshPtr pMesh = pChunk->GetMesh();
			m_faceCount += pMesh->GetVertexCount() / 3;


			const Coord& chunk_origin = pChunk->GetKey().ToChunkOrigin();
			Coord region_origin = VoxelUtils::ToRegionOrigin(chunk_origin);

			OctreePtr pRoot = FindOctree(region_origin);
						
			if(pRoot == nullptr)
			{
				pRoot = pool_manager()->AllocOctTree(region_origin);
				pRoot->SetBound(math::AABBox(math::Vector3(0, 0, 0), math::Vector3((float)REGION_SIZE, (float)REGION_SIZE, (float)REGION_SIZE)));

				m_octrees.push_back(pRoot);
			}
			
			pRoot->AddChunk(pChunk);

		}
		void OctreeManager::RemoveChunk(ChunkPtr pChunk)
		{
			if(pChunk == nullptr)
			{
				return;
			}
			ChunkMeshPtr pMesh = pChunk->GetMesh();
			
			if(pMesh)
			{
				m_faceCount -= pMesh->GetVertexCount() / 3;
			}

			const Coord& chunk_origin = pChunk->GetKey().ToChunkOrigin();
			Coord region_origin = VoxelUtils::ToRegionOrigin(chunk_origin);

			OctreePtr pRoot = FindOctree(region_origin);
						
			if(pRoot == nullptr)
			{
				return;
			}
			
			pRoot->RemoveChunk(pChunk);

			if(pRoot->GetChunkCount() == 0)
			{
				m_octrees.remove(pRoot);
			}

		}
		void OctreeManager::FrustumCull(const math::ViewFrustum& vf, const std::function<void(const Coord&, ChunkMeshPtr)>& op)
		{
			for(auto r : m_octrees)
			{
				const Coord& region_pos = r->GetRegionOrigin();

				math::ViewFrustum v = vf;
				math::Vector3 trans = region_pos.ToVector3();
				
				v.Transform(math::MatrixTranslation(-trans));

				r->FrustumCull(v, std::bind(op, region_pos, std::placeholders::_1));
			}
		}




		/*bool Region::RayPick(const math::Ray& r, Coord& block, float& t, math::Vector3& normal)
		{
			using namespace math;
			const Coord& region_origin = VoxelUtils::ToRegionOrigin(m_coord * REGION_SIZE);

			math::Vector3 trans = region_origin.ToVector3();
				
			math::Ray rr = r;

			math::TransformRay(rr, math::MatrixTranslation(-trans));

			AABBox box(Vector3(0, 0, 0), Vector3(REGION_SIZE, REGION_SIZE, REGION_SIZE));

			float t0, t1;
			if(RayIntersect(rr, box, t0, t1) == intersect_none)
			{
				return false;
			}

			Ray new_r;
			new_r.o = (t0 >= 0) ? r.GetPos(t0) : r.o;
			new_r.d = r.d;

			Real dt = 0;

			Coord region_o = VoxelUtils::ToRegionOrigin(m_coord * REGION_SIZE);
			while(true)
			{
				Vector3 p = new_r.GetPos(dt);

				if(m_pChunkManager->IsEmpty(Coord(p) + region_o) == false)
				{
					Vector3 min_coord((uint32)p.x, (uint32)p.y, (uint32)p.z);

					box.Make(min_coord, min_coord + Vector3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

					if(intersect_intersect == RayIntersect(r, box, t0, t1))
					{
						block = Coord(p) + region_o;
						t = t0;
						Vector3 pt = r.GetPos(t0);
						normal = box.PointNormal(pt);
						return true;
					}
				}

				dt += BLOCK_SIZE;
			}

			return false;
		}*/

		int32 OctreeManager::GetFaceCount()
		{
			return m_faceCount;
		}
		uint32 OctreeManager::GetOctreeCount()
		{
			return m_octrees.size();
		}
	}
}
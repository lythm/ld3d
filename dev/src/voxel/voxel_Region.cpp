#include "voxel_pch.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_World.h"
#include "voxel/voxel_WorldGen.h"
#include "voxel_ChunkManager.h"
#include "voxel_ChunkLoader.h"
#include "voxel/voxel_Chunk.h"
#include "voxel_Octree.h"
#include "voxel_PoolManager.h"
#include "voxel/voxel_ChunkMesh.h"
#include "voxel_VoxelUtils.h"

namespace ld3d
{
	namespace voxel
	{
		Region::Region(void)
		{
			m_coord			= Coord();
		}


		Region::~Region(void)
		{

		}
		
		bool Region::Initialize(WorldPtr pWorld, const Coord& coord)
		{
			m_pWorld = pWorld;
			m_pChunkManager = pWorld->GetChunkManager();

			m_coord			= coord;
		

			m_pOctTree = pool_manager()->AllocOctTree(VoxelUtils::ToRegionOrigin(m_coord * REGION_SIZE));
			m_pOctTree->SetBound(math::AABBox(math::Vector3(0, 0, 0), math::Vector3(REGION_SIZE, REGION_SIZE, REGION_SIZE)));
			return true;
		}
		void Region::Release()
		{
			m_coord = Coord();

			m_pChunkManager.reset();
			m_pOctTree.reset();
		}
		
		void Region::FrustumCull(const math::ViewFrustum& vf, const std::function<void(ChunkMeshPtr)>& op)
		{
			m_pOctTree->FrustumCull(vf, op);
		}
		bool Region::RayPick(const math::Ray& r, Coord& block, float& t, math::Vector3& normal)
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
		}
		void Region::AddChunk(ChunkPtr pChunk)
		{
			
			m_pOctTree->AddChunk(pChunk);
		}
		const Coord& Region::GetRegionOrigin()
		{
			return m_pOctTree->GetRegionOrigin();
		}
	}
}


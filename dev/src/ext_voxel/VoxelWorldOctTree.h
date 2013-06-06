#pragma once

#include <boost\enable_shared_from_this.hpp>

namespace ld3d
{
	struct VoxelWorldChunk;
	class VoxelWorldOctTree : public boost::enable_shared_from_this<VoxelWorldOctTree>
	{
	public:
		enum
		{
			INVALID_FACE_ID			= -1,
		};
		VoxelWorldOctTree(void);
		virtual ~VoxelWorldOctTree(void);

		const math::AABBox&					GetBound() const;
		void								SetBound(const math::AABBox& bound);
		
		void								SetChild(int iChild, VoxelWorldOctTreePtr pChild);
		VoxelWorldOctTreePtr				GetChild(int iChild);

		bool								IsLeaf() const;

		bool								AddChunk(VoxelWorldChunk* pChunk);
		
		void								FrustumCull(const ViewFrustum& vf, boost::function<void (VoxelWorldChunk*)> op);

	private:
		bool								SubDivideBound(const math::AABBox& bound, math::AABBox Bounds[8]);
		bool								_add_chunk(VoxelWorldChunk* pChunk);
	private:

		VoxelWorldOctTreePtr				m_pChildren[8];

		math::AABBox						m_bbox;
		
		VoxelWorldChunk*					m_pChunk;
	};
}

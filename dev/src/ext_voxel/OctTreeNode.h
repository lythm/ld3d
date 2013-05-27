#pragma once

#include <boost\enable_shared_from_this.hpp>

namespace ld3d
{
	class OctTreeNode : public boost::enable_shared_from_this<OctTreeNode>
	{
	public:
		enum
		{
			INVALID_FACE_ID			= -1,
		};
		OctTreeNode(void);
		virtual ~OctTreeNode(void);

		const math::AABBox&					GetBound() const;
		void								SetBound(const math::AABBox& bound);
		
		void								SetParent(OctTreeNodePtr pParent);
		OctTreeNodePtr						GetParent();

		void								SetChild(int iChild, OctTreeNodePtr pChild);
		OctTreeNodePtr						GetChild(int iChild);

		bool								IsLeaf() const;
		void								SetLeaf(bool bIsLeaf);

		void								AddFaceId(int iFace);
		int									GetFaceCount() const;
		int									GetFaceId(int ind);
	private:
		bool								m_bLeaf;
		OctTreeNodePtr						m_pChildren[8];
		OctTreeNodePtr						m_pParent;

		math::AABBox						m_bbox;
		std::vector<int>					m_FaceIds;
	};
}

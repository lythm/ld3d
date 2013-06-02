#include "voxel_pch.h"
#include "OctTreeNode.h"


namespace ld3d
{
	OctTreeNode::OctTreeNode(void)
	{
		m_bLeaf					= false;
		m_pParent				= OctTreeNodePtr();

		for(int i = 0; i < 8; ++i)
		{
			m_pChildren[i] = OctTreeNodePtr();
		}
	}

	OctTreeNode::~OctTreeNode(void)
	{
		for(int i = 0; i < 8; ++i)
		{
			m_pChildren[i].reset();
		}
	}
	const math::AABBox& OctTreeNode::GetBound() const
	{
		return m_bbox;
	}
	void OctTreeNode::SetBound(const math::AABBox& bound)
	{
		m_bbox = bound;
	}
	void OctTreeNode::SetParent(OctTreeNodePtr pParent)
	{
		m_pParent = pParent;
	}
	OctTreeNodePtr OctTreeNode::GetParent()
	{
		return m_pParent;
	}
	void OctTreeNode::SetChild(int iChild, OctTreeNodePtr pChild)
	{
		if(pChild)
		{
			pChild->SetParent(shared_from_this());
		}
		m_pChildren[iChild] = pChild;
	}
	OctTreeNodePtr OctTreeNode::GetChild(int iChild)
	{
		return m_pChildren[iChild];
	}

	bool OctTreeNode::IsLeaf() const
	{
		return m_bLeaf;
	}
	void OctTreeNode::SetLeaf(bool bIsLeaf)
	{
		m_bLeaf = bIsLeaf;
	}
	void OctTreeNode::AddFaceId(int iFace)
	{
		m_FaceIds.push_back(iFace);
	}
	int	OctTreeNode::GetFaceCount() const
	{
		return (int)m_FaceIds.size();
	}
	int	OctTreeNode::GetFaceId(int ind)
	{
		return m_FaceIds[ind];
	}

}

#include "core_pch.h"
#include "..\..\include\core\Overlay.h"
#include "core\Material.h"
#include "core\RenderData.h"
#include "core\GeometryData.h"

namespace ld3d
{
	Overlay::Overlay(OverlayPtr pParent)
	{
		m_pParent			= nullptr;
		
		LinkTo(pParent);

		m_zOrder			= 0;
		m_visible			= true;

		m_rect				= math::RectI(0, 0, 1, 1);
	}


	Overlay::~Overlay(void)
	{
		
	}
	void Overlay::Release()
	{
		while(m_children.size() != 0)
		{
			OverlayPtr pNode = m_children.front();
			m_children.pop_front();
			pNode->Release();
		}
		
		m_children.clear();
		Unlink();
	}
	OverlayPtr Overlay::GetParent()
	{
		return m_pParent;
	}
	std::list<OverlayPtr> Overlay::GetChildList()
	{
		return m_children;
	}
	
	void Overlay::LinkTo(OverlayPtr pParent)
	{
		Unlink();

		if(pParent == nullptr)
		{
			return;
		}
		
		m_pParent = pParent;
		m_pParent->m_children.push_back(shared_from_this());
	}
	void Overlay::Unlink()
	{
		if(m_pParent == nullptr)
		{
			return;
		}
		m_pParent->m_children.remove(shared_from_this());
		m_pParent = nullptr;
	}
	
	void Overlay::SortChildren()
	{
		m_children.sort([](OverlayPtr v1, OverlayPtr v2){return v1->GetZOrder() < v2->GetZOrder();});
	}
	int32 Overlay::GetZOrder()
	{
		return m_zOrder;
	}
	void Overlay::SetZOrder(int32 z)
	{
		m_zOrder = z;
	}
	bool Overlay::IsVisible()
	{
		return m_visible;
	}
	void Overlay::Show(bool show)
	{
		m_visible = show;
	}
	math::RectI Overlay::GetRect()
	{
		return m_rect;
	}
	void Overlay::SetRect(const math::RectI& r)
	{
		m_rect = r;
	}
	const std::string& Overlay::GetName()
	{
		return m_name;
	}
	void Overlay::SetName(const std::string& name)
	{
		m_name = name;
	}
	
	RenderDataPtr Overlay::PrepareRenderData()
	{
		return nullptr;
	}
}

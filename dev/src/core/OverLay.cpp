#include "core_pch.h"
#include "..\..\include\core\Overlay.h"
#include "core\Material.h"
#include "core\RenderData.h"
#include "core\GeometryData.h"

namespace ld3d
{
	Overlay::Overlay(UIManagerPtr pUIManager)
	{
		m_pUIManager		= pUIManager;
		m_pParent			= nullptr;
		
		m_zOrder			= 0;
		m_visible			= true;

		m_rect				= math::RectI(0, 0, 1, 1);

		m_inputFocus		= false;
	}


	Overlay::~Overlay(void)
	{
		
	}
	void Overlay::Release()
	{
		OnRelease();

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

		m_pParent->SortChildren();

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

		if(m_pParent)
		{
			m_pParent->SortChildren();
		}
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
	void Overlay::GetScreenCoord(int& x, int& y)
	{
		int offset_x = 0;
		int offset_y = 0;

		if(m_pParent)
		{
			m_pParent->GetScreenCoord(offset_x, offset_y);
		}

		x = m_rect.left + offset_x;
		y = m_rect.top + offset_y;
	}
	void Overlay::GetSize(uint32& w, uint32& h)
	{
		w = m_rect.width();
		h = m_rect.height();
	}
	void Overlay::MoveTo(int x, int y)
	{
		m_rect.move_to(x, y);
	}
	void Overlay::Move(int offset_x, int offset_y)
	{
		m_rect.move(offset_x, offset_y);
	}
	void Overlay::Resize(uint32 w, uint32 h)
	{
		m_rect.resize(w, h);
		OnResize(w, h);
	}
	void Overlay::OnRelease()
	{
	}
	void Overlay::OnResize(uint32 w, uint32 h)
	{
	}
	
	bool Overlay::IsFocus() const
	{
		return m_inputFocus;
	}
	void Overlay::SetFocus(bool bFocus)
	{
		m_inputFocus = bFocus;
	}
}

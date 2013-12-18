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

		m_pMaterial			= nullptr;
		m_pRenderData		= nullptr;
		m_pGeometryData		= nullptr;
	}


	Overlay::~Overlay(void)
	{
		Release();
	}
	void Overlay::Release()
	{
		for(auto v : m_children)
		{
			v->Release();
			v->Unlink();
		}
		m_children.clear();
		Unlink();

		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial = nullptr;
		}
		if(m_pGeometryData)
		{
			m_pGeometryData->Release();
			m_pGeometryData = nullptr;
		}
		m_pRenderData = nullptr;
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
	void Overlay::SetMaterial(MaterialPtr pMaterial)
	{
		m_pMaterial = pMaterial;
	}
	MaterialPtr Overlay::GetMaterial()
	{
		return m_pMaterial;
	}
	RenderDataPtr Overlay::GetRenderData()
	{
		if(m_visible == false)
		{
			return nullptr;
		}
		if(m_pMaterial == nullptr)
		{
			return nullptr;
		}
		return m_pRenderData;
	}
	const std::string& Overlay::GetName()
	{
		return m_name;
	}
	void Overlay::SetName(const std::string& name)
	{
		m_name = name;
	}
}

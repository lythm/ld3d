#include "core_pch.h"
#include "..\..\include\core\Overlay.h"
#include "core\Material.h"
#include "core\RenderData.h"
#include "core\GeometryData.h"

namespace ld3d
{
	Overlay::Overlay(OverlayPtr pParent)
	{
		m_pParent			= pParent;
		m_zOrder			= 0;
		m_visible			= true;

		m_rect				= math::RectI(0, 0, 1, 1);

		m_pMaterial			= nullptr;
		m_pRenderData		= nullptr;
		m_pGeometryData		= nullptr;
	}


	Overlay::~Overlay(void)
	{
		m_children.clear();
		m_pParent = nullptr;
	}
	void Overlay::Release()
	{
		for(auto v : m_children)
		{
			v->Release();
		}
		m_children.clear();
		m_pParent = nullptr;

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
	void Overlay::AddChild(OverlayPtr pChild)
	{
		if(pChild == nullptr)
		{
			return;
		}
		pChild->SetParent(shared_from_this());
		m_children.push_back(pChild);
	}
	void Overlay::SetParent(OverlayPtr pParent)
	{
		m_pParent = pParent;
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
}

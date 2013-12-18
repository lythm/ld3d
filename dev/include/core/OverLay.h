#pragma once

namespace ld3d
{
	class Overlay : public std::enable_shared_from_this<Overlay>
	{
	public:
		Overlay(OverlayPtr pParent = OverlayPtr());
		virtual ~Overlay(void);

		OverlayPtr									GetParent();
		std::list<OverlayPtr>						GetChildList();
		
		void										LinkTo(OverlayPtr pParent);
		void										Unlink();

		void										SortChildren();

		int32										GetZOrder();
		void										SetZOrder(int32 z);

		bool										IsVisible();
		void										Show(bool show);

		math::RectI									GetRect();
		void										SetRect(const math::RectI& r);

		void										SetMaterial(MaterialPtr pMaterial);
		MaterialPtr									GetMaterial();

		RenderDataPtr								GetRenderData();
		void										Release();

		const std::string&							GetName();
		void										SetName(const std::string& name);
	private:

		int32										m_zOrder;

		OverlayPtr									m_pParent;
		std::list<OverlayPtr>						m_children;

		bool										m_visible;

		RenderDataPtr								m_pRenderData;

		math::RectI									m_rect;

		MaterialPtr									m_pMaterial;
		GeometryDataPtr								m_pGeometryData;

		std::string									m_name;
	};
}

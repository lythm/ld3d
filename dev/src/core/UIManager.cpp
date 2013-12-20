#include "core_pch.h"
#include "core/UIManager.h"
#include "core/OverLay.h"
#include "core_utils.h"
#include "core/CoreApi.h"
#include "core/RenderManager.h"
#include "core/Material.h"
#include "core/TextureOverlay.h"
#include "core/HtmlOverlay.h"

namespace ld3d
{
	UIManager::UIManager(void)
	{
		m_pOverlayRoot				= nullptr;
	}


	UIManager::~UIManager(void)
	{
	}
	bool UIManager::Initialize(CoreApiPtr pCore)
	{
		m_pCore						= pCore;
		m_pRenderManager			= pCore->GetRenderManager();
		m_pOverlayRoot				= CreateOverlay("_root_", math::RectI(0, 0, 1, 1));

		return true;
	}
	void UIManager::Release()
	{
		_release_and_reset(m_pOverlayRoot);
	}
	bool UIManager::LoadUI(const std::string& src)
	{
		return true;
	}
	void UIManager::Update(float dt)
	{
		
	}
	void UIManager::_on_key(EventPtr pEvent)
	{
	}
	void UIManager::_on_mouse_move(EventPtr pEvent)
	{
	}
	void UIManager::_on_mouse_button(EventPtr pEvent)
	{
	}
	bool UIManager::DispatchInputEvent(EventPtr pEvent)
	{
		return false;
	}
	void UIManager::AddOverlay(OverlayPtr pLayer)
	{
		if(pLayer)
		{
			pLayer->LinkTo(m_pOverlayRoot);
		}
	}
	
	void UIManager::PrepareForRendering()
	{
		_prepare_render_data(m_pOverlayRoot);
	}
	void UIManager::_prepare_render_data(OverlayPtr pRoot)
	{
		if(pRoot == nullptr)
		{
			return;
		}

		RenderDataPtr pData = pRoot->PrepareRenderData();
		if(pData)
		{
			m_pRenderManager->AddRenderData(layer_overlay, pData);
		}


		std::list<OverlayPtr> child_list = pRoot->GetChildList();
		std::list<OverlayPtr>::iterator begin = child_list.begin();
		std::list<OverlayPtr>::iterator end = child_list.end();

		for(std::list<OverlayPtr>::iterator it = begin; it != end; ++it)
		{
			_prepare_render_data(*it);
		}

		
	}
	OverlayPtr UIManager::CreateOverlay(const std::string& name, const math::RectI& rect)
	{
		OverlayPtr pO = alloc_object<Overlay>();
		pO->SetName(name);
		pO->SetRect(rect);

		pO->LinkTo(m_pOverlayRoot);
		return pO;
	}
	TextureOverlayPtr UIManager::CreateTextureOverlay(const std::string& name, const math::RectI& rect, TexturePtr pTex)
	{
		TextureOverlayPtr pO = alloc_object<TextureOverlay>();
		if(false == pO->Initialize(m_pRenderManager, name, rect, pTex))
		{
			return nullptr;
		}

		pO->LinkTo(m_pOverlayRoot);
		return pO;
	}
	HtmlOverlayPtr UIManager::CreateHtmlOverlay(const std::string& name, const math::RectI& rect)
	{
		HtmlOverlayPtr pO = alloc_object<HtmlOverlay>();
		if(false == pO->Initialize(m_pRenderManager, name, rect))
		{
			return nullptr;
		}

		pO->LinkTo(m_pOverlayRoot);
		return pO;
	}
}

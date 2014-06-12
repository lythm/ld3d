#include "core_pch.h"
#include "core/UIManager.h"
#include "core/OverLay.h"
#include "core_utils.h"
#include "core/CoreApi.h"
#include "core/RenderManager.h"
#include "core/Material.h"
#include "core/TextureOverlay.h"
#include "core/HtmlOverlay.h"
#include "CEFManager.h"

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


		m_pCEFManager				= alloc_object<cef::CEFManager>();
		if(m_pCEFManager->Initialize(m_pCore) == false)
		{
			return false;
		}
		return true;
	}
	void UIManager::Release()
	{
		
		_release_and_reset(m_pOverlayRoot);

		_release_and_reset(m_pCEFManager);

	}
	bool UIManager::LoadUI(const std::string& src)
	{
		return true;
	}
	void UIManager::Update(float dt)
	{
		
	}
	
	bool UIManager::DispatchInputEvent(EventPtr pEvent)
	{
		return true;
	}
	void UIManager::AddOverlay(OverlayPtr pLayer)
	{
		if(pLayer)
		{
			pLayer->LinkTo(m_pOverlayRoot);
		}
	}
	void UIManager::_traverse_tree_preorder(OverlayPtr pRoot, std::function<bool(OverlayPtr)> handler)
	{
		if(pRoot == nullptr)
		{
			return;
		}

		if(false == handler(pRoot))
		{
			return;
		}

		std::list<OverlayPtr> child_list = pRoot->GetChildList();
		std::list<OverlayPtr>::reverse_iterator begin = child_list.rbegin();
		std::list<OverlayPtr>::reverse_iterator end = child_list.rend();

		for(std::list<OverlayPtr>::reverse_iterator it = begin; it != end; ++it)
		{
			_traverse_tree_preorder(*it, handler);
		}
	}
	void UIManager::PrepareForRendering()
	{
		m_pCEFManager->Update();

		RenderManagerPtr pManager = m_pRenderManager;

		_traverse_tree_preorder(m_pOverlayRoot, 
			[&](OverlayPtr pNode)->bool
			{
				if(pNode->IsVisible() == false)
				{
					return false;
				}
				RenderDataPtr pData = pNode->PrepareRenderData();
				if(pData)
				{
					pManager->AddRenderData(layer_overlay, pData);
				}
				return true;
			}
		);

	}
	
	OverlayPtr UIManager::CreateOverlay(const std::string& name, const math::RectI& rect)
	{
		OverlayPtr pO = alloc_object<Overlay>(shared_from_this());
		pO->SetName(name);
		pO->SetRect(rect);

		pO->LinkTo(m_pOverlayRoot);
		return pO;
	}
	TextureOverlayPtr UIManager::CreateTextureOverlay(const std::string& name, const math::RectI& rect, TexturePtr pTex)
	{
		TextureOverlayPtr pO = alloc_object<TextureOverlay>(shared_from_this());
		if(false == pO->Initialize(m_pRenderManager, name, rect, pTex))
		{
			return nullptr;
		}

		pO->LinkTo(m_pOverlayRoot);
		return pO;
	}
	HtmlOverlayPtr UIManager::CreateHtmlOverlay(const std::string& name, const math::RectI& rect, const std::string& url)
	{
		WebpageRendererPtr pRenderer = m_pCEFManager->CreateWebpageRenderer(url);
		if(pRenderer == nullptr)
		{
			return nullptr;
		}
		HtmlOverlayPtr pO = alloc_object<HtmlOverlay>(shared_from_this());
		if(false == pO->Initialize(m_pRenderManager, pRenderer, name, rect))
		{
			return nullptr;
		}

		pO->LinkTo(m_pOverlayRoot);
		return pO;
	}
	OverlayPtr UIManager::PickOverlay()
	{
		return OverlayPtr();
	}
}

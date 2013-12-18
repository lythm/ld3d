#include "core_pch.h"
#include "core/UIManager.h"
#include "core/OverLay.h"
#include "core_utils.h"
#include "core/CoreApi.h"
#include "core/RenderManager.h"

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

		m_pOverlayRoot				= alloc_object<Overlay>();

		return true;
	}
	void UIManager::Release()
	{
		m_pOverlayRoot->Release();
		m_pOverlayRoot.reset();
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
		_collect_render_data(m_pOverlayRoot);
	}
	void UIManager::_collect_render_data(OverlayPtr pRoot)
	{
		if(pRoot == nullptr)
		{
			return;
		}

		std::list<OverlayPtr> child_list = pRoot->GetChildList();
		std::list<OverlayPtr>::iterator begin = child_list.begin();
		std::list<OverlayPtr>::iterator end = child_list.end();

		for(std::list<OverlayPtr>::iterator it = begin; it != end; ++it)
		{
			_collect_render_data(*it);
		}

		RenderDataPtr pData = pRoot->GetRenderData();
		if(pData)
		{
			m_pRenderManager->AddRenderData(layer_overlay, pData);
		}
	}
}

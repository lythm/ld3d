#include "UIViewer.h"



_DLL_API ld3d::GameInterface* CreateGame()
{
	return new ld3d::UIViewer;
}

_DLL_API void DestroyGame(ld3d::GameInterface* pGame)
{
	delete (ld3d::UIViewer*)pGame;
}


namespace ld3d
{
	UIViewer::UIViewer(void)
	{
	}


	UIViewer::~UIViewer(void)
	{
	}
	bool UIViewer::Initialize(ld3d::CoreApiPtr pCore)
	{
		m_pCore = pCore;

		int w = m_pCore->GetRenderManager()->GetFrameBufferWidth();
		int h = m_pCore->GetRenderManager()->GetFrameBufferHeight();

		m_pPage = m_pCore->GetUIManager()->CreateHtmlOverlay("Viewer", math::RectI(0, 0, w, h), "about:blank");

		//m_pPage->LoadPage("file:///./assets/standard/gui/debug_console/wc.html");
		m_pPage->LoadPage("www.youku.com");

		return true;
	}
	void UIViewer::Release()
	{
		m_pPage->Release();
	}
	bool UIViewer::Update(float dt)
	{
		return true;
	}
}

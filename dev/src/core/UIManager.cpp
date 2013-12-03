#include "core_pch.h"
#include "core/UIManager.h"

//#include "Awesomium/WebCore.h"
//#include "Awesomium/WebConfig.h"
//#include "Awesomium/WebView.h"
//#include "Awesomium/STLHelpers.h"
//#include "Awesomium/BitmapSurface.h"

namespace ld3d
{
	UIManager::UIManager(void)
	{
		//m_pWebCore				= nullptr;
	}


	UIManager::~UIManager(void)
	{
	}
	bool UIManager::Initialize(CoreApiPtr pCore)
	{
		m_pCore = pCore;



		/*using namespace Awesomium;

		m_pWebCore = WebCore::Initialize(WebConfig());

		WebView* pView = m_pWebCore->CreateWebView(400, 400);

		WebURL url(WSLit("http://www.baidu.com"));


		pView->LoadURL(url);

		while(pView->IsLoading())
		{
			m_pWebCore->Update();
		}

		os_sleep(300);
		m_pWebCore->Update();


		BitmapSurface* pSurface = (BitmapSurface*)pView->surface();

		pSurface->SaveToJPEG(WSLit("./a.jpg"));*/




		return true;
	}
	void UIManager::Release()
	{
		/*using namespace Awesomium;
		WebCore::Shutdown();*/
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
}

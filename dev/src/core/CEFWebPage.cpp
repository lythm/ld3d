#include "core_pch.h"
#include "CEFWebpage.h"
#include "include/cef_app.h"
#include "include/cef_runnable.h"
#include "core/Texture.h"
#include "core_utils.h"
#include "core/Event.h"

namespace ld3d
{
	namespace cef
	{
		CEFWebpageRenderer::CEFWebpageRenderer(CoreApiPtr pCore, CefRefPtr<CEFWebpage> pPage)
		{
			m_pPage = pPage;
			m_pCore = pCore;

			m_pCore->AddEventHandler(EV_WINMSG, std::bind(&CEFWebpageRenderer::_on_win_msg, this, std::placeholders::_1));
		}

		CEFWebpageRenderer::~CEFWebpageRenderer()
		{
			m_pPage = nullptr;
		}
		void CEFWebpageRenderer::_on_win_msg(EventPtr pEvent)
		{
			Event_WindowMessage* pMsg = (Event_WindowMessage*)pEvent.get();

			m_pPage->HandleWinMsg(pMsg->msg);
		}
		void CEFWebpageRenderer::SetVisible(bool visible)
		{
			m_pPage->SetVisible(visible);
		}
		
		void CEFWebpageRenderer::Release()
		{
			if(m_pPage)
			{
				m_pPage->Destroy();
			}
		}
		void CEFWebpageRenderer::LoadPage(const std::string& url)
		{
			m_pPage->LoadPage(url);
		}
		void CEFWebpageRenderer::SetRenderTarget(TexturePtr pTexture)
		{
			if(m_pPage)
			{
				m_pPage->SetRenderTarget(pTexture);
			}
		}



		CEFWebpage::CEFWebpage(void)
		{
			m_visible = true;
		}


		CEFWebpage::~CEFWebpage(void)
		{
		}
		void CEFWebpage::SetRenderTarget(TexturePtr pTexture)
		{
			m_pTexture = pTexture;
			if(m_pBrowser)
			{
				m_pBrowser->GetHost()->WasResized();
			}
		}

		CefRefPtr<CefDisplayHandler> CEFWebpage::GetDisplayHandler()
		{
			return this;
		}
		CefRefPtr<CefLifeSpanHandler> CEFWebpage::GetLifeSpanHandler()
		{
			return this;
		}
		CefRefPtr<CefLoadHandler> CEFWebpage::GetLoadHandler()
		{
			return this;
		}
		CefRefPtr<CefRenderHandler> CEFWebpage::GetRenderHandler()
		{
			return this;
		}
		void CEFWebpage::OnAfterCreated(CefRefPtr<CefBrowser> browser)
		{
			m_pBrowser = browser;
		}
		void CEFWebpage::OnBeforeClose(CefRefPtr<CefBrowser> browser)
		{
			m_pBrowser = nullptr;
		}
		void CEFWebpage::OnLoadError(CefRefPtr<CefBrowser> browser, 
			CefRefPtr<CefFrame> frame,
			ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl)
		{
			logger() << "CEF: " << "error[" << errorCode << "] " << errorText.ToString() << " when loading: " << failedUrl.ToString() << "\n";
		}

		bool CEFWebpage::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
		{
			if(m_pTexture == nullptr)
			{
				return false;
			}

			rect.x = 0;
			rect.y = 0;


			rect.width = m_pTexture->GetWidth();
			rect.height = m_pTexture->GetHeight();

			return true;
		}
		void CEFWebpage::OnPaint(CefRefPtr<CefBrowser> browser,
			PaintElementType type,
			const RectList& dirtyRects,
			const void* buffer,
			int width, int height)
		{

			if(m_pTexture == nullptr || IsVisible() == false)
			{
				return;
			}

			m_pTexture->UpdateTextureBGRA8(buffer);

			/*void* pData = m_pTexture->Map();

			memcpy(pData, buffer, width * height * 4);

			m_pTexture->UnMap();*/
		}
		void CEFWebpage::Destroy()
		{
			m_pBrowser->GetHost()->CloseBrowser(true);
			m_pTexture = nullptr;

		}
		
		void CEFWebpage::SetVisible(bool bVisible)
		{
			m_visible = bVisible;
		}
		bool CEFWebpage::IsVisible()
		{
			return m_visible;
		}
		void CEFWebpage::LoadPage(const std::string& url)
		{
			CefString cef_url;
			cef_url.FromString(url);
			m_pBrowser->GetMainFrame()->LoadURL(cef_url);
		}
		void CEFWebpage::HandleWinMsg(MSG& msg)
		{
			switch(msg.message)
			{
			case WM_SETFOCUS:
			case WM_KILLFOCUS:
			     m_pBrowser->GetHost()->SendFocusEvent(msg.message == WM_SETFOCUS);
				 break;
			case WM_SYSCHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_CHAR: 
				{
					CefKeyEvent event;
					event.windows_key_code		= msg.wParam;
					event.native_key_code		= msg.lParam;
					event.is_system_key			= msg.message == WM_SYSCHAR || msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP;
					event.character				 = msg.wParam;

					if (msg.message == WM_KEYDOWN || msg. message == WM_SYSKEYDOWN)
					{
						event.type = KEYEVENT_RAWKEYDOWN;
					}
					else if (msg.message == WM_KEYUP || msg.message == WM_SYSKEYUP)
					{
						event.type = KEYEVENT_KEYUP;
					}
					else
					{
						event.type = KEYEVENT_CHAR;
					}
					event.modifiers = GetCefKeyboardModifiers(msg.wParam, msg.lParam);
					m_pBrowser->GetHost()->SendKeyEvent(event);

					break;
				}
			default:
				break;
			}
		}

		bool CEFWebpage::IsKeyDown(WPARAM wparam) 
		{
			return (GetKeyState(wparam) & 0x8000) != 0;
		}
		int CEFWebpage::GetCefKeyboardModifiers(WPARAM wparam, LPARAM lparam)
		{
			int modifiers = 0;
			if (IsKeyDown(VK_SHIFT))
				modifiers |= EVENTFLAG_SHIFT_DOWN;
			if (IsKeyDown(VK_CONTROL))
				modifiers |= EVENTFLAG_CONTROL_DOWN;
			if (IsKeyDown(VK_MENU))
				modifiers |= EVENTFLAG_ALT_DOWN;

			// Low bit set from GetKeyState indicates "toggled".
			if (::GetKeyState(VK_NUMLOCK) & 1)
				modifiers |= EVENTFLAG_NUM_LOCK_ON;
			if (::GetKeyState(VK_CAPITAL) & 1)
				modifiers |= EVENTFLAG_CAPS_LOCK_ON;

			switch (wparam) 
			{
			case VK_RETURN:
				if ((lparam >> 16) & KF_EXTENDED)
					modifiers |= EVENTFLAG_IS_KEY_PAD;
				break;
			case VK_INSERT:
			case VK_DELETE:
			case VK_HOME:
			case VK_END:
			case VK_PRIOR:
			case VK_NEXT:
			case VK_UP:
			case VK_DOWN:
			case VK_LEFT:
			case VK_RIGHT:
				if (!((lparam >> 16) & KF_EXTENDED))
					modifiers |= EVENTFLAG_IS_KEY_PAD;
				break;
			case VK_NUMLOCK:
			case VK_NUMPAD0:
			case VK_NUMPAD1:
			case VK_NUMPAD2:
			case VK_NUMPAD3:
			case VK_NUMPAD4:
			case VK_NUMPAD5:
			case VK_NUMPAD6:
			case VK_NUMPAD7:
			case VK_NUMPAD8:
			case VK_NUMPAD9:
			case VK_DIVIDE:
			case VK_MULTIPLY:
			case VK_SUBTRACT:
			case VK_ADD:
			case VK_DECIMAL:
			case VK_CLEAR:
				modifiers |= EVENTFLAG_IS_KEY_PAD;
				break;
			case VK_SHIFT:
				if (IsKeyDown(VK_LSHIFT))
					modifiers |= EVENTFLAG_IS_LEFT;
				else if (IsKeyDown(VK_RSHIFT))
					modifiers |= EVENTFLAG_IS_RIGHT;
				break;
			case VK_CONTROL:
				if (IsKeyDown(VK_LCONTROL))
					modifiers |= EVENTFLAG_IS_LEFT;
				else if (IsKeyDown(VK_RCONTROL))
					modifiers |= EVENTFLAG_IS_RIGHT;
				break;
			case VK_MENU:
				if (IsKeyDown(VK_LMENU))
					modifiers |= EVENTFLAG_IS_LEFT;
				else if (IsKeyDown(VK_RMENU))
					modifiers |= EVENTFLAG_IS_RIGHT;
				break;
			case VK_LWIN:
				modifiers |= EVENTFLAG_IS_LEFT;
				break;
			case VK_RWIN:
				modifiers |= EVENTFLAG_IS_RIGHT;
				break;
			}
			return modifiers;
		}
	}
}

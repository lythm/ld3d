#include "core_pch.h"
#include "CEFWebpage.h"
#include "include/cef_app.h"
#include "include/cef_runnable.h"
#include "core/Texture.h"
#include "core_utils.h"
#include "core/Event.h"


#include <windowsx.h>

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
		void CEFWebpageRenderer::SetScreenCoord(int x, int y)
		{
			m_pPage->SetScreenCoord(x, y);
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

			m_screenX = m_screenY = 0;
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

		void CEFWebpage::GetMouseLocalCoord(LPARAM lParam, int& x, int& y)
		{
			x = GET_X_LPARAM(lParam);
			y = GET_Y_LPARAM(lParam);

			x -= m_screenX;
			y -= m_screenY;
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

			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
				{
					int x = 0;
					int y = 0;

					GetMouseLocalCoord(msg.lParam, x, y);

					CefBrowserHost::MouseButtonType btnType =
						(msg.message == WM_LBUTTONDOWN ? MBT_LEFT : (
						msg.message == WM_RBUTTONDOWN ? MBT_RIGHT : MBT_MIDDLE));

					if (m_pBrowser.get()) 
					{
						CefMouseEvent mouse_event;
						mouse_event.x = x;
						mouse_event.y = y;
						mouse_event.modifiers = GetCefMouseModifiers(msg.wParam);
						m_pBrowser->GetHost()->SendMouseClickEvent(mouse_event, btnType, false, 1);
					}
				}
				break;

			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
				{
					int x = 0;
					int y = 0;

					GetMouseLocalCoord(msg.lParam, x, y);

					CefBrowserHost::MouseButtonType btnType =
						(msg.message == WM_LBUTTONUP ? MBT_LEFT : (
						msg.message == WM_RBUTTONUP ? MBT_RIGHT : MBT_MIDDLE));
					if (m_pBrowser.get()) 
					{
						CefMouseEvent mouse_event;
						mouse_event.x = x;
						mouse_event.y = y;
						
						mouse_event.modifiers = GetCefMouseModifiers(msg.wParam);
						m_pBrowser->GetHost()->SendMouseClickEvent(mouse_event, btnType, true, 1);
					}
				}
				break;

			case WM_MOUSEMOVE: 
				{
					int x = 0;
					int y = 0;

					GetMouseLocalCoord(msg.lParam, x, y);

					if (m_pBrowser.get())
					{
						CefMouseEvent mouse_event;
						mouse_event.x = x;
						mouse_event.y = y;
						mouse_event.modifiers = GetCefMouseModifiers(msg.wParam);
						m_pBrowser->GetHost()->SendMouseMoveEvent(mouse_event, false);
					}
				}
				break;

			/*case WM_MOUSELEAVE:

				if (m_pBrowser.get()) 
				{
					CefMouseEvent mouse_event;
					mouse_event.x = 0;
					mouse_event.y = 0;
					mouse_event.modifiers = GetCefMouseModifiers(msg.wParam);
					m_pBrowser->GetHost()->SendMouseMoveEvent(mouse_event, true);
				}
				break;*/

			case WM_MOUSEWHEEL:
				if (m_pBrowser.get())
				{
					POINT screen_point = {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)};

					if(IsPointInside(screen_point.x, screen_point.y) == false)
					{
						break;
					}
					int delta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
					
					int x = 0;
					int y = 0;

					GetMouseLocalCoord(msg.lParam, x, y);

					CefMouseEvent mouse_event;
					mouse_event.x = x;
					mouse_event.y = y;

					mouse_event.modifiers = GetCefMouseModifiers(msg.wParam);

					m_pBrowser->GetHost()->SendMouseWheelEvent(mouse_event, IsKeyDown(VK_SHIFT) ? delta : 0, !IsKeyDown(VK_SHIFT) ? delta : 0);
				}
				break;
			case WM_CAPTURECHANGED:
			case WM_CANCELMODE:
				if (m_pBrowser.get())
				{
					m_pBrowser->GetHost()->SendCaptureLostEvent();
				}
				break;
			default:
				break;
			}
		}
		bool CEFWebpage::IsPointInside(int screenX, int screenY)
		{
			if(screenX < m_screenX || screenX > m_screenX + m_pTexture->GetWidth())
			{
				return false;
			}

			if(screenY < m_screenY || screenY > m_screenY + m_pTexture->GetHeight())
			{
				return false;
			}

			return true;
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
		int CEFWebpage::GetCefMouseModifiers(WPARAM wparam)
		{
			int modifiers = 0;
			if (wparam & MK_CONTROL)
				modifiers |= EVENTFLAG_CONTROL_DOWN;
			if (wparam & MK_SHIFT)
				modifiers |= EVENTFLAG_SHIFT_DOWN;
			if (IsKeyDown(VK_MENU))
				modifiers |= EVENTFLAG_ALT_DOWN;
			if (wparam & MK_LBUTTON)
				modifiers |= EVENTFLAG_LEFT_MOUSE_BUTTON;
			if (wparam & MK_MBUTTON)
				modifiers |= EVENTFLAG_MIDDLE_MOUSE_BUTTON;
			if (wparam & MK_RBUTTON)
				modifiers |= EVENTFLAG_RIGHT_MOUSE_BUTTON;

			// Low bit set from GetKeyState indicates "toggled".
			if (::GetKeyState(VK_NUMLOCK) & 1)
				modifiers |= EVENTFLAG_NUM_LOCK_ON;
			if (::GetKeyState(VK_CAPITAL) & 1)
				modifiers |= EVENTFLAG_CAPS_LOCK_ON;
			return modifiers;
		}
		void CEFWebpage::SetScreenCoord(int x, int y)
		{
			m_screenX = x;
			m_screenY = y;
		}
		void CEFWebpage::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
		{
			int i = 0;
		}
	}
}

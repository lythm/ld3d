#include "core_pch.h"
#include "CEFWebPage.h"
#include "include/cef_app.h"
#include "include/cef_runnable.h"
#include "core/Texture.h"
#include "core_utils.h"
#include "core/Event.h"

namespace ld3d
{
	namespace cef
	{
		CEFWebpageRenderer::CEFWebpageRenderer(CefRefPtr<CEFWebPage> pPage)
		{
			m_pPage = pPage;
		}

		CEFWebpageRenderer::~CEFWebpageRenderer()
		{
			m_pPage = nullptr;
		}

		bool CEFWebpageRenderer::ProcessInput(EventPtr pEvent)
		{
			return m_pPage->ProcessInput(pEvent);
		}
		void CEFWebpageRenderer::Release()
		{
			if(m_pPage)
			{
				m_pPage->Destroy();
			}
		}
		void CEFWebpageRenderer::SetRenderTarget(TexturePtr pTexture)
		{
			if(m_pPage)
			{
				m_pPage->SetRenderTarget(pTexture);
			}
		}



		CEFWebPage::CEFWebPage(void)
		{
		}


		CEFWebPage::~CEFWebPage(void)
		{
		}
		void CEFWebPage::SetRenderTarget(TexturePtr pTexture)
		{
			m_pTexture = pTexture;
			if(m_pBrowser)
			{
				m_pBrowser->GetHost()->WasResized();
			}
		}

		CefRefPtr<CefDisplayHandler> CEFWebPage::GetDisplayHandler()
		{
			return this;
		}
		CefRefPtr<CefLifeSpanHandler> CEFWebPage::GetLifeSpanHandler()
		{
			return this;
		}
		CefRefPtr<CefLoadHandler> CEFWebPage::GetLoadHandler()
		{
			return this;
		}
		CefRefPtr<CefRenderHandler> CEFWebPage::GetRenderHandler()
		{
			return this;
		}
		void CEFWebPage::OnAfterCreated(CefRefPtr<CefBrowser> browser)
		{
			m_pBrowser = browser;
		}
		void CEFWebPage::OnBeforeClose(CefRefPtr<CefBrowser> browser)
		{
			m_pBrowser = nullptr;
		}
		void CEFWebPage::OnLoadError(CefRefPtr<CefBrowser> browser, 
			CefRefPtr<CefFrame> frame,
			ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl)
		{
			logger() << "CEF: " << "error[" << errorCode << "] " << errorText.ToString() << " when loading: " << failedUrl.ToString() << "\n";
		}

		bool CEFWebPage::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
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
		void CEFWebPage::OnPaint(CefRefPtr<CefBrowser> browser,
			PaintElementType type,
			const RectList& dirtyRects,
			const void* buffer,
			int width, int height)
		{

			if(m_pTexture == nullptr)
			{
				return;
			}

			m_pTexture->UpdateTextureBGRA8(buffer);

			/*void* pData = m_pTexture->Map();

			memcpy(pData, buffer, width * height * 4);

			m_pTexture->UnMap();*/
		}
		void CEFWebPage::Destroy()
		{
			m_pBrowser->GetHost()->CloseBrowser(true);
			m_pTexture = nullptr;

		}
		bool CEFWebPage::ProcessInput(EventPtr pEvent)
		{
			m_pBrowser->GetHost()->SendFocusEvent(true);

			switch(pEvent->id)
			{
			case EV_CHAR:
				{
					Event_Char* pChar = (Event_Char*)pEvent.get();
					CefKeyEvent cef_key;

					cef_key.character = pChar->key_code;
					cef_key.focus_on_editable_field = true;
					cef_key.is_system_key = false;
					cef_key.native_key_code = pChar->key_code;
					cef_key.type = KEYEVENT_CHAR;
					cef_key.windows_key_code = pChar->key_code;
					m_pBrowser->GetHost()->SendKeyEvent(cef_key);

					//// backspace
					//if(pChar->key_code == 8)
					//{
					//	cef_key.type = KEYEVENT_KEYDOWN;
					//
					//	m_pBrowser->GetHost()->SendKeyEvent(cef_key);
					//}
				}
				break;
			case EV_KEYBOARD_STATE:
				{
					Event_KeyboardState* pKey = (Event_KeyboardState*)pEvent.get();
					CefKeyEvent cef_key;

					cef_key.character = pKey->vk_code;
					cef_key.focus_on_editable_field = true;
					cef_key.is_system_key = false;
					cef_key.native_key_code = pKey->key_code;
					cef_key.type = pKey->keyboard_state->KeyDown(pKey->key_code) ? KEYEVENT_KEYDOWN : KEYEVENT_KEYUP;
					cef_key.windows_key_code = pKey->vk_code;
					m_pBrowser->GetHost()->SendKeyEvent(cef_key);
				}
				break;
			default:
				break;

			}
			return true;
		}
	}
}

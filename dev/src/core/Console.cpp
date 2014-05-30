#include "core_pch.h"
#include "Console.h"

#include "core/CoreApi.h"

#include "core/HtmlOverlay.h"
#include "core/UIManager.h"
#include "core/RenderManager.h"
#include "core/Event.h"

namespace ld3d
{
	Console::Console(void)
	{
	}


	Console::~Console(void)
	{
	}
	bool Console::Initialize(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		int w = m_pCore->GetRenderManager()->GetFrameBufferWidth();
		int h = m_pCore->GetRenderManager()->GetFrameBufferHeight();

		m_pConsoleWnd = m_pCore->GetUIManager()->CreateHtmlOverlay("sys_console", math::RectI(0, 0, w, h / 2), "file:///assets/standard/gui/console/index.html");

		m_pConsoleWnd->LoadPage("file:///assets/standard/gui/console/index.html");

		m_pConsoleWnd->SetZOrder(-1);

		m_pCore->AddEventHandler(EV_KEYBOARD_STATE, std::bind(&Console::_on_key, this, std::placeholders::_1));
		return true;
	}
	void Console::Show(bool show)
	{
		m_pConsoleWnd->Show(show);
	}
	void Console::Release()
	{
		_release_and_reset(m_pConsoleWnd);
		m_pCore = nullptr;
	}
	void Console::_on_key(EventPtr pEvent)
	{
		Event_KeyboardState* pKey = (Event_KeyboardState*)pEvent.get();
		
		if(pKey->key_code == key_grave && pKey->keyboard_state->KeyDown(key_grave) == false)
		{
			Show(!m_pConsoleWnd->IsVisible());
		}
	}
}

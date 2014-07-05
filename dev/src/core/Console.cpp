#include "core_pch.h"
#include "core/Console.h"

#include "core/CoreApi.h"

#include "core/HtmlOverlay.h"
#include "core/UIManager.h"
#include "core/RenderManager.h"
#include "core/Event.h"
#include "core/WebpageRenderer.h"
#include "core/Screen.h"
#include "core/Sys_Graphics.h"

#include "core_utils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
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

	//	m_pConsoleWnd->LoadPage("file:///assets/standard/gui/console/index.html");

		m_pConsoleWnd->SetZOrder(-1);

		m_pCore->AddEventHandler(EV_KEYBOARD_STATE, std::bind(&Console::_on_key, this, std::placeholders::_1));
		m_pCore->AddEventHandler(EV_RESIZE_FRAMEBUFFER, std::bind(&Console::_on_resize, this, std::placeholders::_1));


		m_pConsoleWnd->GetWebpageRenderer()->RegisterScriptCallHandler("on_console_command", std::bind(&Console::_on_cmd, this, std::placeholders::_1));


		RegisterConsoleCommand("exit", std::bind(&Console::_on_cmd_exit, this, std::placeholders::_1, std::placeholders::_2));
		RegisterConsoleCommand("help", std::bind(&Console::_on_cmd_help, this, std::placeholders::_1, std::placeholders::_2));
		RegisterConsoleCommand("show_debug_panel", std::bind(&Console::_on_cmd_show_debug_panel, this, std::placeholders::_1, std::placeholders::_2));
		RegisterConsoleCommand("set_windowed", std::bind(&Console::_on_cmd_set_windowed, this, std::placeholders::_1, std::placeholders::_2));
		RegisterConsoleCommand("set_resolution", std::bind(&Console::_on_cmd_set_resolution, this, std::placeholders::_1, std::placeholders::_2));
		RegisterConsoleCommand("get_gl_ext", std::bind(&Console::_on_cmd_get_gl_ext, this, std::placeholders::_1, std::placeholders::_2));
		
		return true;
	}
	void Console::Show(bool show)
	{
		m_pConsoleWnd->Show(show);
	}
	void Console::Release()
	{
		m_cmdMap.clear();
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
	void Console::_on_resize(EventPtr pEvent)
	{
		Event_ResizeFrameBuffer* pResize = (Event_ResizeFrameBuffer*)pEvent.get();
		
		m_pConsoleWnd->Resize(pResize->w, pResize->h / 2);
	}
	void Console::_on_cmd(const std::string& json)
	{
		using namespace boost::property_tree;

		
		ptree pt;

		try
		{
			std::stringstream stream(json);
			
			read_json(stream, pt);
		}
		catch(json_parser_error& e)
		{
			logger() << e.what() << "\n";
			WriteLine(e.what());
		}

		std::string cmdline = pt.get<std::string>("parameter");

		CommandLine cl(cmdline.c_str());

		std::string cmd = cl.GetCmd();

		std::map<std::string, std::function<void (const CommandLine&, std::function<void (const std::string&)>)>>::iterator it = m_cmdMap.find(cmd);
		if(it == m_cmdMap.end())
		{
			WriteLine("unknown command: " + cmd);
			return;
		}

		it->second(cl, std::bind(&Console::WriteLine, this, std::placeholders::_1));
	}
	void Console::WriteLine(const std::string& str)
	{
		m_pConsoleWnd->GetWebpageRenderer()->ExecuteJS("con.writeln('"+str+"');");
	}
	void Console::_on_cmd_exit(const CommandLine& cl, std::function<void (const std::string&)>)
	{
		m_pCore->QuitApp();
	}
	bool Console::RegisterConsoleCommand(const std::string& cmd, const std::function<void (const CommandLine&, std::function<void (const std::string&)>)>& handler)
	{
		std::map<std::string, std::function<void (const CommandLine&, std::function<void (const std::string&)>)>>::iterator it = m_cmdMap.find(cmd);
		if(it != m_cmdMap.end())
		{
			return false;
		}

		m_cmdMap[cmd] = handler;

		return true;
	}
	void Console::RemoveConsoleCommand(const std::string& cmd)
	{
		std::map<std::string, std::function<void (const CommandLine&, std::function<void (const std::string&)>)>>::iterator it = m_cmdMap.find(cmd);
		if(it == m_cmdMap.end())
		{
			return;			
		}

		m_cmdMap.erase(it);
	}
	void Console::_on_cmd_help(const CommandLine& cl, std::function<void (const std::string&)>)
	{
		for(auto cmd : m_cmdMap)
		{
			WriteLine("-" + cmd.first);
		}

		WriteLine("total " + boost::lexical_cast<std::string>(m_cmdMap.size()) + " commands.");
	}
	void Console::_on_cmd_show_debug_panel(const CommandLine& cl, std::function<void (const std::string&)>)
	{
		if(cl.GetParamCount() == 0)
		{
			m_pCore->ShowDebugPanel(true);
			return;
		}

		if(cl.GetParamCount() == 1)
		{
			bool value = false;
			try
			{
				value = boost::lexical_cast<bool>(cl.GetParam(0));
			}
			catch (boost::bad_lexical_cast& e)
			{
				WriteLine(std::string("invalid parameter type: ") + e.what());
				return;
			}
			m_pCore->ShowDebugPanel(value);
			return;
		}

		WriteLine("invalid parameters.");
	}
	void Console::_on_cmd_set_windowed(const CommandLine& cl, std::function<void (const std::string&)>)
	{
		if(cl.GetParamCount() != 1)
		{
			WriteLine("invalid parameters");
			return;
		}

		bool value = false;
		try
		{
			value = boost::lexical_cast<bool>(cl.GetParam(0));
		}
		catch (boost::bad_lexical_cast& e)
		{
			WriteLine(std::string("invalid parameter type: ") + e.what());
			return;
		}
		ScreenPtr pScreen = m_pCore->GetScreen();

		pScreen->SetWindowed(value);
	}
	void Console::_on_cmd_set_resolution(const CommandLine& cl, std::function<void (const std::string&)>)
	{
		if(cl.GetParamCount() != 2)
		{
			WriteLine("invalid parameters");
			return;
		}

		int w = 0;
		int h = 0;

		try
		{
			w = boost::lexical_cast<int>(cl.GetParam(0));
			h = boost::lexical_cast<int>(cl.GetParam(1));
		}
		catch (boost::bad_lexical_cast& e)
		{
			WriteLine(std::string("invalid parameter type: ") + e.what());
			return;
		}

		if(w == 0 || h == 0)
		{
			WriteLine("invalid value");
			return;
		}
		ScreenPtr pScreen = m_pCore->GetScreen();

		pScreen->SetResolution(w, h);
	}
	void Console::_on_cmd_get_gl_ext(const CommandLine& cl, std::function<void (const std::string&)>)
	{
		if(cl.GetParamCount() != 0)
		{
			WriteLine("invalid parameters");
			return;
		}

		std::vector<std::string> exts = m_pCore->GetSysGraphics()->GetGLExtensions();

		for(auto s : exts)
		{
			WriteLine(s);

			logger() << s << "\n";
		}
	}
}


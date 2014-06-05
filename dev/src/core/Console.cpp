#include "core_pch.h"
#include "core/Console.h"

#include "core/CoreApi.h"

#include "core/HtmlOverlay.h"
#include "core/UIManager.h"
#include "core/RenderManager.h"
#include "core/Event.h"
#include "core/WebpageRenderer.h"

#include "core_utils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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


		m_pConsoleWnd->GetWebpageRenderer()->RegisterScriptCallHandler("on_console_command", std::bind(&Console::_on_cmd, this, std::placeholders::_1));


		RegisterConsoleCommand("exit", std::bind(&Console::_on_cmd_exit, this, std::placeholders::_1, std::placeholders::_2));
		RegisterConsoleCommand("help", std::bind(&Console::_on_cmd_help, this, std::placeholders::_1, std::placeholders::_2));
		RegisterConsoleCommand("show_debug_panel", std::bind(&Console::_on_cmd_show_debug_panel, this, std::placeholders::_1, std::placeholders::_2));
		
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
	void Console::_on_cmd(const std::string& json)
	{
		using namespace boost::property_tree;

		
		ptree pt;

		try
		{
			read_json(std::stringstream(json), pt);
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
}


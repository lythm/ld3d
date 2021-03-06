#pragma once

namespace ld3d
{
	class Console
	{
	public:
		Console(void);
		virtual ~Console(void);


		bool												Initialize(CoreApiPtr pCore);
		void												Release();

		void												Show(bool show);

		void												WriteLine(const std::string& str);

		bool												RegisterConsoleCommand(const std::string& cmd, const std::function<void (const CommandLine&, std::function<void (const std::string&)>)>& handler);
		void												RemoveConsoleCommand(const std::string& cmd);
	private:
		void												_on_key(EventPtr pEvent);
		void												_on_resize(EventPtr pEvent);


		void												_on_cmd(const std::string& json);

		void												_on_cmd_exit(const CommandLine& cl, std::function<void (const std::string&)>);
		void												_on_cmd_help(const CommandLine& cl, std::function<void (const std::string&)>);
		void												_on_cmd_show_debug_panel(const CommandLine& cl, std::function<void (const std::string&)>);
		void												_on_cmd_set_windowed(const CommandLine& cl, std::function<void (const std::string&)>);
		void												_on_cmd_set_resolution(const CommandLine& cl, std::function<void (const std::string&)>);
		void												_on_cmd_get_gl_ext(const CommandLine& cl, std::function<void (const std::string&)>);

		
	private:
		HtmlOverlayPtr										m_pConsoleWnd;
		CoreApiPtr											m_pCore;


		std::map<std::string, 
			std::function<void (const CommandLine&, 
				std::function<void (const std::string&)>)>>		m_cmdMap;

	};
}

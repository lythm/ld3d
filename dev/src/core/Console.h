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


		void												_on_cmd(const std::string& json);

		void												_on_cmd_exit(const CommandLine& cl, std::function<void (const std::string&)>);
		void												_on_cmd_help(const CommandLine& cl, std::function<void (const std::string&)>);
	private:
		HtmlOverlayPtr										m_pConsoleWnd;
		CoreApiPtr											m_pCore;


		std::map<std::string, 
			std::function<void (const CommandLine&, 
				std::function<void (const std::string&)>)>>		m_cmdMap;

	};
}

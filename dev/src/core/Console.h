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

	private:
		void												_on_key(EventPtr pEvent);
	private:
		HtmlOverlayPtr										m_pConsoleWnd;
		CoreApiPtr											m_pCore;


		

	};
}

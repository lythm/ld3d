#pragma once

namespace ld3d
{
	class Console
	{
	public:
		Console(void);
		virtual ~Console(void);


		bool												Initialize();
		void												Release();
	private:
		HtmlOverlayPtr										m_pConsoleWnd;
	};


}
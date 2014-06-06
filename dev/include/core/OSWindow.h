#pragma once

namespace ld3d
{
	class Window
	{
	public:
		Window(void){}

		virtual ~Window(void){}

		virtual void										Destroy()							= 0;
		virtual void										Show(bool show)						= 0;
		virtual void										IsVisible()							= 0;
		virtual void										Resize(int cx, int cy)				= 0;
		virtual void										SetFullscreen(bool fullscreen)		= 0;

	protected:
		
	};
}

#pragma once

namespace ld3d
{
	class RenderWindow
	{
	public:

		virtual int															GetWidth()					= 0;
		virtual int															GetHeight()					= 0;
		virtual void														Release()					= 0;
	protected:
		RenderWindow(void){}
		virtual ~RenderWindow(void){}
	};
}
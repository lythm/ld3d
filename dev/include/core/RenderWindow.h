#pragma once

#include "core/RenderTarget.h"

namespace ld3d
{
	class RenderWindow : public RenderTarget
	{
	public:

		virtual int															GetWidth()													= 0;
		virtual int															GetHeight()													= 0;
		virtual void														Release()													= 0;
	protected:
		RenderWindow(void) : RenderTarget(RENDER_WINDOW){}
		virtual ~RenderWindow(void){}
	};

	
}

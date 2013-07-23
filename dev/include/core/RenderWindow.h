#pragma once

#include "core\RenderTarget.h"

namespace ld3d
{
	class RenderWindow2 : public RenderTarget2
	{
	public:

		virtual int															GetWidth()													= 0;
		virtual int															GetHeight()													= 0;
		virtual void														Release()													= 0;
	protected:
		RenderWindow2(void) : RenderTarget2(RENDER_WINDOW){}
		virtual ~RenderWindow2(void){}
	};

	
}

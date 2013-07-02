#pragma once

#include "core\RenderWindow.h"

namespace ld3d
{
	class OGL4RenderWindow : public RenderWindow
	{
	public:
		OGL4RenderWindow(void);
		virtual ~OGL4RenderWindow(void);

		bool														Create();
		int															GetWidth();
		int															GetHeight();
		void														Release();


	};


}
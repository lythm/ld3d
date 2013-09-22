#pragma once


namespace ld3d
{
	class RenderSystem
	{
	public:

		RenderSystem(void)
		{
		}

		virtual ~RenderSystem(void)
		{
		}

		virtual void								Render()						= 0;
	};
}

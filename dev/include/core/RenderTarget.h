#pragma once

namespace ld3d
{
	class RenderTarget2
	{
	public:
		enum TARGET_TYPE
		{
			RENDER_TEXTURE,
			RENDER_WINDOW,
		};
		virtual void											Release()														= 0;
		

		TARGET_TYPE												GetType(){return m_type;}


		RenderTarget2(TARGET_TYPE type){m_type = type;}
		virtual ~RenderTarget2(void){}

	protected:
		TARGET_TYPE												m_type;
	};
}

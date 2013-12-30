#pragma once

namespace ld3d
{
	class WebpageRenderer
	{
	public:

		WebpageRenderer(void){}

		virtual ~WebpageRenderer(void){}

		virtual void										SetRenderTarget(TexturePtr pTarget)							= 0;
		virtual void										Release()													= 0;
		virtual void										SetVisible(bool visible)									= 0;
		virtual void										LoadPage(const std::string& url)							= 0;
		virtual void										SetScreenCoord(int x, int y)								= 0;
	};
}

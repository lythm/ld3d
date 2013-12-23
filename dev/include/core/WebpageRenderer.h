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

	};
}

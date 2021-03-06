#pragma once

namespace ld3d
{
	class _DLL_CLASS PostEffect
	{
	public:
		PostEffect(void);
		virtual ~PostEffect(void);

		virtual void									Render(RenderManagerPtr pRenderer, RenderTexturePtr pInput, RenderTexturePtr pOutput)					= 0;
		virtual void									Release()																								= 0;
	};
}

#pragma once

namespace ld3d
{
	class EXPORT_CLASS PostEffect
	{
	public:
		PostEffect(void);
		virtual ~PostEffect(void);

		virtual void									Render(RenderManagerPtr pRenderer, RenderTexture2Ptr pInput, RenderTexture2Ptr pOutput)						= 0;
		virtual void									Release()																								= 0;
	};
}

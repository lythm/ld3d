#pragma once

namespace ld3d
{
	namespace cef
	{
		class CEFWebPage
		{
		public:
			CEFWebPage(void);
			virtual ~CEFWebPage(void);

			void												SetRenderTarget(TexturePtr pTexture);
		};
	}
}

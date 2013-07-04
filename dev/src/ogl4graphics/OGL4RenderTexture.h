#pragma once

#include "core/RenderWindow.h"

namespace ld3d
{
	class OGL4RenderTexture : public RenderTexture2
	{
	public:
		OGL4RenderTexture(void);
		virtual ~OGL4RenderTexture(void);


		bool														Create(int w, int h, G_FORMAT format);
		void														Release();
		
		int															GetWidth();
		int															GetHeight();

		TexturePtr													AsTexture();


	private:
		OGL4TexturePtr												m_pTex;
		
	};


}
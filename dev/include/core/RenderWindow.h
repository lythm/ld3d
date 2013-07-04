#pragma once

#include "core\RenderTarget.h"

namespace ld3d
{
	class RenderWindow
	{
	public:

		virtual int															GetWidth()					= 0;
		virtual int															GetHeight()					= 0;
		virtual void														Release()					= 0;
	protected:
		RenderWindow(void){}
		virtual ~RenderWindow(void){}
	};


	class RenderWindow2 : public RenderTarget2
	{
	public:

		virtual int															GetWidth()							= 0;
		virtual int															GetHeight()							= 0;
		virtual void														Release()							= 0;
	protected:
		RenderWindow2(void){}
		virtual ~RenderWindow2(void){}
	};

	class RenderTexture2 : public RenderTarget2
	{
	public:
		virtual int															GetWidth()							= 0;
		virtual int															GetHeight()							= 0;
		virtual void														Release()							= 0;
		virtual TexturePtr													AsTexture()							= 0;
	};
}

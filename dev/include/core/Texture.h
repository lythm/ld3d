#pragma once

#include "g_format.h"

namespace ld3d
{
	class _DLL_CLASS Texture
	{
	public:
		
		Texture(void){}
		virtual ~Texture(void){}

		virtual TEXTURE_TYPE								GetType()								= 0;

		virtual void										Release()								= 0;

		virtual void*										Map()									= 0;
		virtual void										UnMap()									= 0;

		virtual void										SetSampler(SamplerStatePtr pSampler)	= 0;
		virtual SamplerStatePtr								GetSampler()							= 0;	

		virtual int											GetWidth() const						= 0;
		virtual int											GetHeight() const						= 0;
		virtual int											GetDepth() const						= 0;
		virtual int											GetLvls() const							= 0;
		virtual int											GetLayers() const						= 0;
		virtual void										GenMipmap()								= 0;
		virtual bool										IsMultiSample(){return false;}

		virtual void										UpdateTextureBGRA8(const void* data)	= 0;
	};
}

#pragma once

#include "g_format.h"

namespace ld3d
{
	class EXPORT_CLASS Texture
	{
	public:
		
		Texture(void){}
		virtual ~Texture(void){}

		virtual TEXTURE_TYPE								GetType()								= 0;

		virtual void										Release()								= 0;

	};


	class EXPORT_CLASS Texture2
	{
	public:
		
		Texture2(void){}
		virtual ~Texture2(void){}

		virtual TEXTURE_TYPE								GetType()								= 0;

		virtual void										Release()								= 0;

		virtual void*										Map()									= 0;
		virtual void										UnMap()									= 0;

	};
}

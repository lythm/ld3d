#pragma once

#include "core/Texture.h"

namespace ld3d
{
	class OGL4Texture : public Texture
	{
	public:
		OGL4Texture(void);
		virtual ~OGL4Texture(void);

		TEXTURE_TYPE								GetType();

		void										Release();
	};


}
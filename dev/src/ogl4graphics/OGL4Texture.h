#pragma once

#include "core/Texture.h"

namespace ld3d
{
	class OGL4Texture : public Texture
	{
	public:
		OGL4Texture(void);
		virtual ~OGL4Texture(void);


		bool										Create(TEXTURE_TYPE type, G_FORMAT format, int w, int h);

		TEXTURE_TYPE								GetType();

		void										Release();

	private:
		GLuint										m_texture;
		int											m_width;
		int											m_height;
		TEXTURE_TYPE								m_type;
	};
}

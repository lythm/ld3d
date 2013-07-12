#pragma once

#include "core/Texture.h"

namespace ld3d
{
	class OGL4Texture : public Texture2
	{
	public:
		OGL4Texture(void);
		virtual ~OGL4Texture(void);

		TEXTURE_TYPE								GetType();

		void										Release();


		void										SetSampler(SamplerStatePtr pSampler);
		SamplerStatePtr								GetSampler();	
		bool										Create1D(G_FORMAT format, int l, bool dynamic);
		bool										Create2D(G_FORMAT format, int w, int h, bool dynamic);
		bool										Create3D(G_FORMAT format, int w, int h, int d, bool dynamic);

		bool										CreateFromFile(const char* szFile, bool dynamic);

		void*										Map();
		void										UnMap();

		GLuint										GetTextureObject();
	private:
		unsigned int								FormatSize(GLenum format);

		GLenum										TransferFormat(GLenum format);
		GLenum										TransferType(GLenum format);
	private:
		GLuint										m_pbo;
		GLuint										m_texture;
		int											m_width;
		int											m_height;
		int											m_depth;
		TEXTURE_TYPE								m_type;
		GLenum										m_format;

		int											m_pboBytes;
		bool										m_bDynamic;

		SamplerStatePtr								m_pSampler;
	};
}

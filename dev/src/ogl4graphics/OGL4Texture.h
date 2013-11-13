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

		bool										IsMultiSample();

		void										SetSampler(SamplerStatePtr pSampler);
		SamplerStatePtr								GetSampler();	
		bool										Create1D(G_FORMAT format, int l, int lvls, bool dynamic);
		bool										Create2D(G_FORMAT format, int w, int h, int lvls, bool dynamic);
		bool										Create2DMS(G_FORMAT format, int w, int h, int samples);
		bool										Create2DShadow(G_FORMAT format, int w, int h);
		bool										Create3D(G_FORMAT format, int w, int h, int d, int lvls, bool dynamic);

		int											GetWidth() const;
		int											GetHeight() const;
		int											GetDepth() const;
		int											GetLvls() const;
		bool										CreateFromFile(const char* szFile);

		void*										Map();
		void										UnMap();

		GLuint										GetTextureObject();

		void										GenMipmap();
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

		int											m_lvls;

		bool										m_bMS;
	};
}

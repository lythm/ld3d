#pragma once

#include "core/Texture.h"


namespace gli
{
	class storage;

};
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
		bool										Create2DArray(G_FORMAT format, int w, int h, int lvls, int layers, bool dynamic);
		int											GetWidth() const;
		int											GetHeight() const;
		int											GetDepth() const;
		int											GetLvls() const;
		int											GetLayers() const;
		bool										CreateFromFile(const char* szFile);
		bool										Create2DArrayFromFiles(const std::vector<std::string>& files);
		void*										Map();
		void										UnMap();

		GLuint										GetTextureObject();

		void										GenMipmap();

		void										UpdateTextureBGRA8(const void* data);
	private:
		bool										CreateCubemapFromFile(const gli::storage& s);
		bool										Create2DFromFile(const gli::storage& s);
		bool										Create2DArrayFromFile(const gli::storage& s);
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
		int											m_layers;
		bool										m_bMS;
	};
}

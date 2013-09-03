#include "ogl4graphics_pch.h"
#include "OGL4Texture.h"
#include "OGL4Convert.h"

#include "gli/gli.hpp"

namespace ld3d
{

	OGL4Texture::OGL4Texture(void)
	{
		m_pbo					= 0;
		m_texture				= 0;
		m_width					= 0;
		m_height				= 0;
		m_type					= TEX_UNKNOWN;
		m_format				= GL_INVALID_ENUM;

		m_bDynamic				= false;

		m_lvls					= 1;
	}


	OGL4Texture::~OGL4Texture(void)
	{
	}
	TEXTURE_TYPE OGL4Texture::GetType()
	{
		return TEX_2D;
	}
	void OGL4Texture::Release()
	{
		glDeleteBuffers(1, &m_pbo);
		m_pbo = 0;
		glDeleteTextures(1, &m_texture);
		m_texture = 0;
	}
	bool OGL4Texture::Create1D(G_FORMAT format, int l, int lvls, bool dynamic)
	{
		m_lvls = lvls;
		m_bDynamic = dynamic;
		glGenTextures(1, &m_texture);

		glBindTexture(GL_TEXTURE_1D, m_texture);

		glTexStorage1D(GL_TEXTURE_1D, lvls, OGL4Convert::TextureFormatToGL(format), l);

		m_width = l;
		m_type = TEX_1D;

		m_format = OGL4Convert::TextureFormatToGL(format);

		m_pboBytes = FormatSize(m_format) * m_width;
		return true;
	}
	bool OGL4Texture::Create2D(G_FORMAT format, int w, int h, int lvls, bool dynamic)
	{
		m_lvls = lvls;
		m_bDynamic = dynamic;

		glGenTextures(1, &m_texture);

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexStorage2D(GL_TEXTURE_2D, lvls, OGL4Convert::TextureFormatToGL(format), w, h);

		m_width = w;
		m_height = h;
		m_type = TEX_2D;

		m_format = OGL4Convert::TextureFormatToGL(format);

		m_pboBytes = FormatSize(m_format) * m_width * m_height;
		return true;
	}

	bool OGL4Texture::Create3D(G_FORMAT format, int w, int h, int d, int lvls, bool dynamic)
	{
		m_lvls = lvls;
		m_bDynamic = dynamic;

		glGenTextures(1, &m_texture);

		glBindTexture(GL_TEXTURE_3D, m_texture);
		glTexStorage3D(GL_TEXTURE_3D, lvls, OGL4Convert::TextureFormatToGL(format), w, h, d);

		m_width = w;
		m_height = h;
		m_type = TEX_3D;;
		m_depth = d;

		m_format = OGL4Convert::TextureFormatToGL(format);

		m_pboBytes = FormatSize(m_format) * m_width * m_height * m_depth;
		return true;
	}
	void* OGL4Texture::Map()
	{

		if(m_pbo == 0)
		{
			glGenBuffers(1, &m_pbo);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbo);
			glBufferData(GL_PIXEL_UNPACK_BUFFER, m_pboBytes, nullptr, m_bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );
		}
		else
		{
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbo);
		}

		return glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, m_pboBytes, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	}
	void OGL4Texture::UnMap()
	{

		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

		switch(m_type)
		{
		case TEX_1D:
			glBindTexture(GL_TEXTURE_1D, m_texture);
			glTexSubImage1D(GL_TEXTURE_1D, 0, 0, m_width, TransferFormat(m_format), TransferType(m_format), 0);
			glBindTexture(GL_TEXTURE_1D, 0);
			break;
		case TEX_2D:
			glBindTexture(GL_TEXTURE_2D, m_texture);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, TransferFormat(m_format), TransferType(m_format), 0);

			glBindTexture(GL_TEXTURE_2D, 0);
			break;
		case TEX_3D:
			glBindTexture(GL_TEXTURE_3D, m_texture);
			glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, m_width, m_height, m_depth, TransferFormat(m_format), TransferType(m_format), 0);
			glBindTexture(GL_TEXTURE_3D, 0);
			break;
		default:
			assert(0);
			break;
		}


		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}

	unsigned int OGL4Texture::FormatSize(GLenum format)
	{
		switch(format)
		{
		case GL_R8:
		case GL_R8_SNORM:
			return 1;
		case GL_R16:
		case GL_R16_SNORM:
			return 2;

		case GL_RG8:
		case GL_RG8_SNORM:
			return 2;
		case GL_RG16:
		case GL_RG16_SNORM:
			return 4;

		case GL_RGBA8:
		case GL_RGBA8_SNORM:
			return 4;

		case GL_RGBA16:
		case GL_RGBA16_SNORM:
			return 8;

		case GL_R16F:
			return 2;
		case GL_RG16F:
			return 4;

		case GL_RGBA16F:
			return 8;

		case GL_R32F:
			return 4;

		case GL_RG32F:
			return 8;

		case GL_RGB32F:
			return 12;

		case GL_RGBA32F:
			return 16;

		case GL_R11F_G11F_B10F:
			return 4;

		case GL_R8I:
		case GL_R8UI:
			return 1;

		case GL_R16I:
		case GL_R16UI:
			return 2;

		case GL_R32I:
		case GL_R32UI:
			return 4;

		case GL_RG8I:
		case GL_RG8UI:
			return 2;

		case GL_RG16I:
		case GL_RG16UI:
			return 4;

		case GL_RG32I:
		case GL_RG32UI:
			return 8;


		case GL_RGBA8I:
		case GL_RGBA8UI:
			return 4;

		case GL_RGBA16I:

		case GL_RGBA16UI:
			return 8;

		case GL_RGB32I:
		case GL_RGB32UI:
			return 12;

		case GL_RGBA32I:
		case GL_RGBA32UI:
			return 16;
		default:
			assert(0);
			break;
		}

		return 0;
	}
	GLenum OGL4Texture::TransferFormat(GLenum format)
	{
		switch(format)
		{
		case GL_R8:
		case GL_R8_SNORM:
		case GL_R16:
		case GL_R16_SNORM:
		case GL_R16F:
		case GL_R32F:
		case GL_R8I:
		case GL_R8UI:
		case GL_R16I:
		case GL_R16UI:
		case GL_R32I:
		case GL_R32UI:
			return GL_RED;

		case GL_RG8:
		case GL_RG8_SNORM:
		case GL_RG16:
		case GL_RG16_SNORM:
		case GL_RG16F:
		case GL_RG32F:
		case GL_RG8I:
		case GL_RG8UI:
		case GL_RG16I:
		case GL_RG16UI:
		case GL_RG32I:
		case GL_RG32UI:
			return GL_RG;

		case GL_RGBA8:
		case GL_RGBA8_SNORM:
		case GL_RGBA16:
		case GL_RGBA16_SNORM:
		case GL_RGBA16F:
		case GL_RGBA32F:
		case GL_RGBA8I:
		case GL_RGBA8UI:
		case GL_RGBA16I:
		case GL_RGBA16UI:
		case GL_RGBA32I:
		case GL_RGBA32UI:
			return GL_RGBA;

		case GL_RGB32F:
		case GL_R11F_G11F_B10F:
		case GL_RGB32I:
		case GL_RGB32UI:
			return GL_RGB;

		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}

	GLenum OGL4Texture::TransferType(GLenum format)
	{
		switch(format)
		{
		case GL_RGBA8:
		case GL_RG8:
		case GL_R8:
		case GL_R8UI:
		case GL_RG8UI:
		case GL_RGBA8UI:
			return GL_UNSIGNED_BYTE;
		case GL_R8_SNORM:
		case GL_R8I:
		case GL_RG8_SNORM:
		case GL_RG8I:
		case GL_RGBA8I:
		case GL_RGBA8_SNORM:
			return GL_BYTE;

		case GL_RGBA16:
		case GL_RG16:
		case GL_R16:
		case GL_R16UI:
		case GL_RG16UI:
		case GL_RGBA16UI:
			return GL_UNSIGNED_SHORT;
		case GL_R16_SNORM:
		case GL_RGBA16I:
		case GL_R16I:
		case GL_RG16_SNORM:
		case GL_RGBA16_SNORM:
		case GL_RG16I:
			return GL_SHORT;

		case GL_RGBA16F:
		case GL_R16F:
		case GL_RG16F:
			return GL_HALF_FLOAT;
		case GL_RG32F:
		case GL_R32F:
		case GL_RGBA32F:
		case GL_RGB32F:
		case GL_R11F_G11F_B10F:
			return GL_FLOAT;

		case GL_R32I:
		case GL_RGBA32I:
		case GL_RGB32I:
		case GL_RG32I:
			return GL_INT;
		case GL_R32UI:
		case GL_RGB32UI:
		case GL_RG32UI:
		case GL_RGBA32UI:
			return GL_UNSIGNED_INT;

		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLuint OGL4Texture::GetTextureObject()
	{
		return m_texture;
	}
	//bool OGL4Texture::CreateFromFile(const char* szFile, bool dynamic)
	//{
	//	m_bDynamic = dynamic;

	//	m_texture = SOIL_load_OGL_texture(szFile, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	//	if(m_texture == 0)
	//		return false;

	//	
	//	m_type = TEX_2D;
	//	
	//	// todo
	//	/*m_width = w;
	//	m_lvls = 1;
	//	m_height = h;
	//	m_depth = d;

	//	m_format = OGL4Convert::TextureFormatToGL(format);

	//	m_pboBytes = FormatSize(m_format) * m_width * m_height * m_depth;*/


	//	return true;
	//}

	bool OGL4Texture::CreateFromFile(const char* szFile, bool dynamic)
	{
		m_bDynamic = dynamic;


		glGenTextures(1, &m_texture);

		gli::texture2D tex(gli::loadStorageDDS(szFile));

		if(tex.empty())
		{
			return false;
		}

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(tex.levels() - 1));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
		glTexStorage2D(GL_TEXTURE_2D,
			GLint(tex.levels()),
			GLenum(gli::internal_format(tex.format())),
			GLsizei(tex.dimensions().x),
			GLsizei(tex.dimensions().y));
		if(gli::is_compressed(tex.format()))
		{
			for(gli::texture2D::size_type Level = 0; Level < tex.levels(); ++Level)
			{
				glCompressedTexSubImage2D(GL_TEXTURE_2D,
					GLint(Level),
					0, 0,
					GLsizei(tex[Level].dimensions().x),
					GLsizei(tex[Level].dimensions().y),
					GLenum(gli::internal_format(tex.format())),
					GLsizei(tex[Level].size()),
					tex[Level].data());
			}
		}
		else
		{
			for(gli::texture2D::size_type Level = 0; Level < tex.levels(); ++Level)
			{
				glTexSubImage2D(GL_TEXTURE_2D,
					GLint(Level),
					0, 0,
					GLsizei(tex[Level].dimensions().x),
					GLsizei(tex[Level].dimensions().y),
					GLenum(gli::external_format(tex.format())),
					GLenum(gli::type_format(tex.format())),
					tex[Level].data());
			}
		}


		m_type = TEX_2D;

		// todo
		m_width = tex.dimensions().x;
		m_height = tex.dimensions().y;
		m_lvls = tex.levels();
		m_depth = 0;

		m_format = GLenum(gli::internal_format(tex.format()));

//		m_pboBytes = FormatSize(m_format) * m_width * m_height;

		return true;
	}

	void OGL4Texture::SetSampler(SamplerStatePtr pSampler)
	{
		m_pSampler = pSampler;

	}
	SamplerStatePtr OGL4Texture::GetSampler()
	{
		return m_pSampler;
	}
	int  OGL4Texture::GetWidth() const
	{
		return m_width;
	}
	int  OGL4Texture::GetHeight() const
	{
		return m_height;
	}
	int	 OGL4Texture::GetDepth() const
	{
		return m_depth;
	}
}

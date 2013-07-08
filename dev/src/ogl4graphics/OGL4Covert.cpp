#include "ogl4graphics_pch.h"
#include "OGL4Covert.h"

namespace ld3d
{
	OGL4Covert::OGL4Covert(void)
	{
	}


	OGL4Covert::~OGL4Covert(void)
	{
	}
	GLenum OGL4Covert::BufferTypeToGLTarget(BUFFER_TYPE type)
	{
		switch(type)
		{
		case BT_VERTEX_BUFFER:

			return GL_ARRAY_BUFFER;

		case BT_INDEX_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLenum OGL4Covert::PrimitiveTypeToGL(PRIMITIVE_TYPE type)
	{
		switch(type)
		{
		case PT_TRIANGLE_LIST:
			return GL_TRIANGLES;
		case PT_TRIANGLE_STRIP:
			return GL_TRIANGLE_STRIP;
		case PT_LINE_LIST:
			return GL_LINES;
		default:
			assert(0);
		}
		return GL_INVALID_ENUM;
	}
	GLenum OGL4Covert::ShaderTypeToGL(SHADER_TYPE type)
	{
		switch(type)
		{
		case ST_VERTEX_SHADER:
			return GL_VERTEX_SHADER;
		case ST_PIXEL_SHADER:
			return GL_FRAGMENT_SHADER;
		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLenum OGL4Covert::TexTypeToGLTarget(TEXTURE_TYPE type)
	{
		switch(type)
		{
		case TEX_1D:
			return GL_TEXTURE_1D;
		case TEX_2D:
			return GL_TEXTURE_2D;
		case TEX_3D:
			return GL_TEXTURE_3D;
		default:
			break;
		}
		return GL_INVALID_ENUM;
	}
	bool OGL4Covert::FormatToGLVertexAttr(G_FORMAT format, unsigned int &value_count, GLenum& gltype)
	{
		switch(format)
		{
		case G_FORMAT_R32G32B32A32_FLOAT:
			value_count = 4;
			gltype = GL_FLOAT;
			return true;
		case G_FORMAT_R32G32B32A32_UINT:
			value_count = 4;
			gltype = GL_UNSIGNED_INT;
			return true;
		case G_FORMAT_R32G32B32A32_SINT:
			value_count = 4;
			gltype = GL_INT;
			return true;

		case G_FORMAT_R32G32B32_FLOAT:
			value_count = 3;
			gltype = GL_FLOAT;
			return true;
		case G_FORMAT_R32G32B32_UINT:
			value_count = 3;
			gltype = GL_UNSIGNED_INT;
			return true;
		case G_FORMAT_R32G32B32_SINT:
			value_count = 3;
			gltype = GL_INT;
			return true;


		case G_FORMAT_R16G16B16A16_FLOAT:
			value_count = 4;
			gltype = GL_HALF_FLOAT;
			return true;
		case G_FORMAT_R16G16B16A16_UINT:
			value_count = 4;
			gltype = GL_UNSIGNED_SHORT;
			return true;
		case G_FORMAT_R16G16B16A16_SINT:
			value_count = 4;
			gltype = GL_SHORT;
			return true;

		case G_FORMAT_R32G32_FLOAT:
			value_count = 2;
			gltype = GL_FLOAT;

			return true;
		case G_FORMAT_R32G32_UINT:
			value_count = 2;
			gltype = GL_UNSIGNED_INT;

			return true;
		case G_FORMAT_R32G32_SINT:
			value_count = 2;
			gltype = GL_INT;

			return true;

		case G_FORMAT_R16G16_FLOAT:
			value_count = 2;
			gltype = GL_HALF_FLOAT;
			return true;
		case G_FORMAT_R16G16_UINT:
			value_count = 2;
			gltype = GL_UNSIGNED_SHORT;
			return true;
		case G_FORMAT_R16G16_SINT:
			value_count = 2;
			gltype = GL_SHORT;
			return true;
		case G_FORMAT_R32_FLOAT:
			value_count = 1;
			gltype = GL_FLOAT;
			return true;
		case G_FORMAT_R32_UINT:
			value_count = 1;
			gltype = GL_UNSIGNED_INT;
			return true;
		case G_FORMAT_R32_SINT:
			value_count = 1;
			gltype = GL_INT;
			return true;

		case G_FORMAT_R16_FLOAT:
			value_count = 1;
			gltype = GL_HALF_FLOAT;
			return true;
		case G_FORMAT_R16_UINT:
			value_count = 1;
			gltype = GL_UNSIGNED_SHORT;
			return true;
		case G_FORMAT_R16_SINT:
			value_count = 1;
			gltype = GL_SHORT;
			return true;
		case G_FORMAT_R8_UINT:
			value_count = 1;
			gltype = GL_UNSIGNED_BYTE;
			return true;
		case G_FORMAT_R8_SINT:
			value_count = 1;
			gltype = GL_BYTE;
			return true;
		default:
			assert(0);
			break;
		}

		return false;
	}
}
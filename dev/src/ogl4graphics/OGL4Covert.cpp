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
}
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

}
#include "ogl4graphics_pch.h"
#include "OGL4Convert.h"

namespace ld3d
{
	OGL4Convert::OGL4Convert(void)
	{
	}


	OGL4Convert::~OGL4Convert(void)
	{
	}
	GLenum OGL4Convert::BufferTypeToGLTarget(BUFFER_TYPE type)
	{
		switch(type)
		{
		case BT_VERTEX_BUFFER:

			return GL_ARRAY_BUFFER;

		case BT_INDEX_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;

		case BT_CONSTANT_BUFFER:
			return GL_UNIFORM_BUFFER;

		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLenum OGL4Convert::PrimitiveTypeToGL(PRIMITIVE_TYPE type)
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
	GLenum OGL4Convert::ShaderTypeToGL(SHADER_TYPE type)
	{
		switch(type)
		{
		case ST_VERTEX_SHADER:
			return GL_VERTEX_SHADER;
		case ST_PIXEL_SHADER:
			return GL_FRAGMENT_SHADER;
		case ST_GEOMETRY_SHADER:
			return GL_GEOMETRY_SHADER;

		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLenum OGL4Convert::TexTypeToGLTarget(TEXTURE_TYPE type)
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
	bool OGL4Convert::FormatToGLVertexAttr(G_FORMAT format, unsigned int &value_count, GLenum& gltype)
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



	GLenum OGL4Convert::TextureFormatToGL(G_FORMAT type)
	{
		switch(type)
		{
		case G_FORMAT_R8_UNORM:
			return GL_R8;
		case G_FORMAT_R8_SNORM:
			return GL_R8_SNORM;
		case G_FORMAT_R16_UNORM:
			return GL_R16;
		case G_FORMAT_R16_SNORM:
			return GL_R16_SNORM;

		case G_FORMAT_R8G8_UNORM:
			return GL_RG8;
		case G_FORMAT_R8G8_SNORM:
			return GL_RG8_SNORM;
		case G_FORMAT_R16G16_UNORM:
			return GL_RG16;
		case G_FORMAT_R16G16_SNORM:
			return GL_RG16_SNORM;

		case G_FORMAT_R8G8B8A8_UNORM:
			return GL_RGBA8;
		case G_FORMAT_R8G8B8A8_SNORM:
			return GL_RGBA8_SNORM;

		case G_FORMAT_R16G16B16A16_UNORM:
			return GL_RGBA16;
		case G_FORMAT_R16G16B16A16_SNORM:
			return GL_RGBA16_SNORM;

		case G_FORMAT_R16_FLOAT:
			return GL_R16F;
		case G_FORMAT_R16G16_FLOAT:
			return GL_RG16F;

		case G_FORMAT_R16G16B16A16_FLOAT:
			return GL_RGBA16F;

		case G_FORMAT_R32_FLOAT:
			return GL_R32F;

		case G_FORMAT_R32G32_FLOAT:
			return GL_RG32F;

		case G_FORMAT_R32G32B32_FLOAT:
			return GL_RGB32F;

		case G_FORMAT_R32G32B32A32_FLOAT:
			return GL_RGBA32F;

		case G_FORMAT_R11G11B10_FLOAT:
			return GL_R11F_G11F_B10F;

		case G_FORMAT_R8_SINT:
			return GL_R8I;
		case G_FORMAT_R8_UINT:
			return GL_R8UI;

		case G_FORMAT_R16_SINT:
			return GL_R16I;
		case G_FORMAT_R16_UINT:
			return GL_R16UI;

		case G_FORMAT_R32_SINT:
			return GL_R32I;
		case G_FORMAT_R32_UINT:
			return GL_R32UI;

		case G_FORMAT_R8G8_SINT:
			return GL_RG8I;
		case G_FORMAT_R8G8_UINT:
			return GL_RG8UI;

		case G_FORMAT_R16G16_SINT:
			return GL_RG16I;
		case G_FORMAT_R16G16_UINT:
			return GL_RG16UI;

		case G_FORMAT_R32G32_SINT:
			return GL_RG32I;
		case G_FORMAT_R32G32_UINT:
			return GL_RG32UI;


		case G_FORMAT_R8G8B8A8_SINT:
			return GL_RGBA8I;
		case G_FORMAT_R8G8B8A8_UINT:
			return GL_RGBA8UI;

		case G_FORMAT_R16G16B16A16_SINT:
			return GL_RGBA16I;
		case G_FORMAT_R16G16B16A16_UINT:
			return GL_RGBA16UI;

		case G_FORMAT_R32G32B32_SINT:
			return GL_RGB32I;
		case G_FORMAT_R32G32B32_UINT:
			return GL_RGB32UI;

		case G_FORMAT_R32G32B32A32_SINT:
			return GL_RGBA32I;
		case G_FORMAT_R32G32B32A32_UINT:
			return GL_RGBA32UI;

		// depth
		case G_FORMAT_D32_FLOAT:
			return GL_DEPTH_COMPONENT32F;
		case G_FORMAT_D24_UNORM_S8_UINT:
			return GL_DEPTH24_STENCIL8;
		case G_FORMAT_D16_UNORM:
			return GL_DEPTH_COMPONENT16;
		case G_FORMAT_D32_FLOAT_S8X24_UINT:
			return GL_DEPTH32F_STENCIL8;

		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLenum OGL4Convert::BlendOPToGL(RS_BLEND_OP op)
	{
		switch(op)
		{
		case RS_BLEND_OP_ADD:
			return GL_FUNC_ADD;
		case RS_BLEND_OP_SUBTRACT:
			return GL_FUNC_SUBTRACT;
		case RS_BLEND_OP_REV_SUBTRACT:
			return GL_FUNC_REVERSE_SUBTRACT;
		case RS_BLEND_OP_MIN:
			return GL_MIN;
		case RS_BLEND_OP_MAX:
			return GL_MAX;
		default:
			assert(0);
			break;
		}
		return GL_INVALID_ENUM;
	}

	GLenum OGL4Convert::BlendToGL(RS_BLEND val)
	{
		switch(val)
		{
		case RS_BLEND_ZERO:
			return GL_ZERO;
		case RS_BLEND_ONE:
			return GL_ONE;
		case RS_BLEND_SRC_COLOR:
			return GL_SRC_COLOR;
		case RS_BLEND_INV_SRC_COLOR:
			return GL_ONE_MINUS_SRC_COLOR;
		case RS_BLEND_SRC_ALPHA:
			return GL_SRC_ALPHA;
		case RS_BLEND_INV_SRC_ALPHA:
			return GL_ONE_MINUS_SRC_ALPHA;
		case RS_BLEND_DEST_ALPHA:
			return GL_DST_ALPHA;
		case RS_BLEND_INV_DEST_ALPHA:
			return GL_ONE_MINUS_DST_ALPHA;
		case RS_BLEND_DEST_COLOR:
			return GL_DST_COLOR;
		case RS_BLEND_INV_DEST_COLOR:
			return GL_ONE_MINUS_DST_COLOR;
		case RS_BLEND_SRC_ALPHA_SAT:
			return GL_SRC_ALPHA_SATURATE;
		case RS_BLEND_BLEND_FACTOR:
			return GL_CONSTANT_COLOR;;
		case RS_BLEND_INV_BLEND_FACTOR:
			return GL_ONE_MINUS_CONSTANT_COLOR;
		//case RS_BLEND_SRC1_COLOR:
		//	return GL_SRC1_COLOR;
		//case RS_BLEND_INV_SRC1_COLOR:
		//	return GL_ONE_MINUS_SRC1_COLOR;
		//case RS_BLEND_SRC1_ALPHA:
		//	return GL_SRC1_ALPHA;
		//case RS_BLEND_INV_SRC1_ALPHA:
		//	return GL_ONE_MINUS_SRC1_ALPHA;
		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLenum OGL4Convert::FillModeToGL(RS_FILL_MODE mode)
	{
		switch(mode)
		{
		case RS_FILL_SOLID:
			return GL_FILL;
		case RS_FILL_WIREFRAME:
			return GL_LINE;
		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
	GLenum OGL4Convert::CompareFuncToGL(RS_COMPARISON_FUNC func)
	{
		switch(func)
		{
		case RS_COMPARISON_NEVER:
			return GL_NEVER;
		case RS_COMPARISON_LESS:
			return GL_LESS;
		case RS_COMPARISON_EQUAL:
			return GL_EQUAL;
		case RS_COMPARISON_LESS_EQUAL:
			return GL_LEQUAL;
		case RS_COMPARISON_GREATER:
			return GL_GREATER;
		case RS_COMPARISON_NOT_EQUAL:
			return GL_NOTEQUAL;
		case RS_COMPARISON_GREATER_EQUAL:
			return GL_GEQUAL;
		case RS_COMPARISON_ALWAYS:
			return GL_ALWAYS;

		default:
			assert(0);
			break;
		}
		return GL_INVALID_ENUM;
	}
	GLenum OGL4Convert::StencilOPToGL(RS_STENCIL_OP op)
	{
		switch(op)
		{
		case RS_STENCIL_OP_KEEP:
			return GL_KEEP;
		case RS_STENCIL_OP_ZERO:
			return GL_ZERO;
		case RS_STENCIL_OP_REPLACE:
			return GL_REPLACE;
		case RS_STENCIL_OP_INCR_SAT:
			return GL_INCR_WRAP;
		case RS_STENCIL_OP_DECR_SAT:
			return GL_DECR_WRAP;
		case RS_STENCIL_OP_INVERT:
			return GL_INVERT;
		case RS_STENCIL_OP_INCR:
			return GL_INCR;
		case RS_STENCIL_OP_DECR:
			return GL_DECR;
		default:
			assert(0);
			break;
		}
		return GL_INVALID_ENUM;
	}
}

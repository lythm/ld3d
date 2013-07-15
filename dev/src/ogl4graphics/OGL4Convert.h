#pragma once


namespace ld3d
{
	class OGL4Convert
	{
	public:

		static GLenum												BufferTypeToGLTarget(BUFFER_TYPE type);
		static GLenum												PrimitiveTypeToGL(PRIMITIVE_TYPE type);
		static GLenum												TexTypeToGLTarget(TEXTURE_TYPE type);

		static GLenum												TextureFormatToGL(G_FORMAT type);

		static bool													FormatToGLVertexAttr(G_FORMAT format, unsigned int &value_count, GLenum& gltype);
		static GLenum												ShaderTypeToGL(SHADER_TYPE type);

		static GLenum												BlendOPToGL(RS_BLEND_OP op);
		static GLenum												BlendToGL(RS_BLEND val);
		static GLenum												FillModeToGL(RS_FILL_MODE mode);

		static GLenum												CompareFuncToGL(RS_COMPARISON_FUNC func);

		static GLenum												StencilOPToGL(RS_STENCIL_OP op);
	private:
		OGL4Convert(void);
		virtual ~OGL4Convert(void);
	};


}
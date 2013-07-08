#pragma once


namespace ld3d
{
	class OGL4Convert
	{
	public:

		static GLenum												BufferTypeToGLTarget(BUFFER_TYPE type);
		static GLenum												PrimitiveTypeToGL(PRIMITIVE_TYPE type);
		static GLenum												TexTypeToGLTarget(TEXTURE_TYPE type);

		static bool													FormatToGLVertexAttr(G_FORMAT format, unsigned int &value_count, GLenum& gltype);
		static GLenum												ShaderTypeToGL(SHADER_TYPE type);
	private:
		OGL4Convert(void);
		virtual ~OGL4Convert(void);
	};


}
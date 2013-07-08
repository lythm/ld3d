#pragma once


namespace ld3d
{
	class OGL4Covert
	{
	public:

		static GLenum												BufferTypeToGLTarget(BUFFER_TYPE type);
		static GLenum												PrimitiveTypeToGL(PRIMITIVE_TYPE type);
		static GLenum												TexTypeToGLTarget(TEXTURE_TYPE type);

		static bool													FormatToGLVertexAttr(G_FORMAT format, unsigned int &value_count, GLenum& gltype);

	private:
		OGL4Covert(void);
		virtual ~OGL4Covert(void);
	};


}
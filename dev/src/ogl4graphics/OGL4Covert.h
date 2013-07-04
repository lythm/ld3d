#pragma once


namespace ld3d
{
	class OGL4Covert
	{
	public:

		static GLenum												BufferTypeToGLTarget(BUFFER_TYPE type);
		static GLenum												PrimitiveTypeToGL(PRIMITIVE_TYPE type);
	private:
		OGL4Covert(void);
		virtual ~OGL4Covert(void);
	};


}
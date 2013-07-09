#pragma once

#include "core\Shader.h"

namespace ld3d
{
	class OGL4Shader : public Shader
	{
	public:
		OGL4Shader(SHADER_TYPE type, GLuint shader);
		virtual ~OGL4Shader(void);


		void								Release();
		SHADER_TYPE							GetType();


		GLuint								GetShaderObject();
	private:
		GLuint								m_shader;
		SHADER_TYPE							m_type;
	};


}
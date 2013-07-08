#pragma once

#include "core\Shader.h"

namespace ld3d
{
	class OGL4Shader : public Shader
	{
	public:
		OGL4Shader(void);
		virtual ~OGL4Shader(void);


		void								Release();
		SHADER_TYPE							GetType();




		bool								CreateFromFile(SHADER_TYPE type, const char* szFile);
		GLuint								GetShaderObject();
	private:
		GLuint								m_shader;
		SHADER_TYPE							m_type;
	};


}
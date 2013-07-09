#include "ogl4graphics_pch.h"
#include "OGL4Shader.h"
#include "OGL4Convert.h"

namespace ld3d
{

	OGL4Shader::OGL4Shader(SHADER_TYPE type, GLuint shader)
	{
		m_shader				= shader;
		m_type					= type;
	}


	OGL4Shader::~OGL4Shader(void)
	{
	}
	void OGL4Shader::Release()
	{
		glDeleteShader(m_shader);
		m_shader = 0;

	}
	SHADER_TYPE OGL4Shader::GetType()
	{
		return m_type;
	}
	
	GLuint OGL4Shader::GetShaderObject()
	{
		return m_shader;
	}
}

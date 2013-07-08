#include "ogl4graphics_pch.h"
#include "OGL4Shader.h"
#include "OGL4Convert.h"

namespace ld3d
{

	OGL4Shader::OGL4Shader(void)
	{
		m_shader				= 0;
		m_type					= ST_VERTEX_SHADER;
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
	bool OGL4Shader::CreateFromFile(SHADER_TYPE type, const char* szFile)
	{
		FILE* file = fopen(szFile, "rb");

		if(file == nullptr)
		{
			return false;
		}

		SCOPE_EXIT(fclose(file));

		fseek(file, 0, SEEK_END);
		
		uint64 size = ftell(file);

		fseek(file, (long)0, SEEK_SET);

		char *szCode = new char[size + 1];
		SCOPE_EXIT(delete[] szCode);

		
		fread(szCode, 1, size, file);

		szCode[size] = 0;
		m_type = type;

		GLenum gltype = OGL4Convert::ShaderTypeToGL(type);
		m_shader = glCreateShader(gltype);

		glShaderSource(m_shader, 1, &szCode, 0);

		glCompileShader(m_shader);

		char szInfo[1024];
		glGetShaderInfoLog(m_shader, 1024, nullptr, szInfo); 
		g_log(szInfo);


		GLint ret = GL_FALSE;
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &ret);
		if(ret == GL_FALSE)
		{
			return false;
		}
		
		return true;
	}
	GLuint OGL4Shader::GetShaderObject()
	{
		return m_shader;
	}
}

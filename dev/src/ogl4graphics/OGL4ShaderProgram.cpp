#include "ogl4graphics_pch.h"
#include "OGL4ShaderProgram.h"
#include "OGL4Shader.h"
#include "OGL4Convert.h"

namespace ld3d
{
	OGL4ShaderProgram::OGL4ShaderProgram(void)
	{
		m_program = 0;
	}


	OGL4ShaderProgram::~OGL4ShaderProgram(void)
	{
	}
	void OGL4ShaderProgram::Release()
	{
		for(auto v : m_shaders)
		{
			glDetachShader(m_program, ((OGL4Shader*)v.get())->GetShaderObject());
			v->Release();
		}
		m_shaders.clear();
		glDeleteProgram(m_program);
		m_program = 0;
	}
	void OGL4ShaderProgram::AttachShader(ShaderPtr pShader)
	{
		m_shaders.push_back(pShader);

		OGL4ShaderPtr pGLShader = std::dynamic_pointer_cast<OGL4Shader>(pShader);

		glAttachShader(m_program, pGLShader->GetShaderObject());
	}
	
	bool OGL4ShaderProgram::AttachShaderFromFile(SHADER_TYPE type, const char* szFile)
	{
		OGL4ShaderPtr pShader = std::make_shared<OGL4Shader>();
		if(pShader->CreateFromFile(type, szFile) == false)
		{
			return false;
		}

		m_shaders.push_back(pShader);

		glAttachShader(m_program, pShader->GetShaderObject());
		
		return true;
	}
	
	bool OGL4ShaderProgram::Link()
	{
		glLinkProgram(m_program);

		char szInfo[1024];
		glGetProgramInfoLog(m_program, 1024, nullptr, szInfo);
		g_log(szInfo);

		GLint ret = GL_FALSE;
		glGetProgramiv(m_program,  GL_LINK_STATUS, &ret);

		if(ret == GL_FALSE)
		{
			return false;
		}

		return true;
	}
	bool OGL4ShaderProgram::Create()
	{
		m_program = glCreateProgram();
		return true;
	}
	void OGL4ShaderProgram::Use()
	{
		glUseProgram(m_program);
	}
	bool OGL4ShaderProgram::Validate()
	{
		glValidateProgram(m_program);

		char szInfo[1024];
		glGetProgramInfoLog(m_program, 1024, nullptr, szInfo);
		g_log(szInfo);

		GLint ret = GL_FALSE;
		glGetProgramiv(m_program,  GL_VALIDATE_STATUS, &ret);

		if(ret == GL_FALSE)
		{
			return false;
		}
		return true;
	}
}

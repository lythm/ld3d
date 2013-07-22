#include "ogl4graphics_pch.h"
#include "OGL4ShaderProgram.h"
#include "OGL4Shader.h"
#include "OGL4Convert.h"
#include "OGL4Buffer.h"
#include <algorithm>
#include "OGL4Texture.h"
#include "OGL4ShaderCompiler.h"
#include "OGL4Sampler.h"

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
		for(auto v : m_uniformBlocks)
		{
			v.pBuffer->Release();
		}
		m_uniformBlocks.clear();

		m_texLinks.clear();

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
		OGL4ShaderPtr pShader = OGL4ShaderCompiler::CreateShaderFromFile(type, szFile);
		if(pShader == nullptr)
		{
			return false;
		}

		m_shaders.push_back(pShader);

		glAttachShader(m_program, pShader->GetShaderObject());
		
		return true;
	}
	void OGL4ShaderProgram::CollectUniformBlocks()
	{
		GLint count = 0;
		glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_BLOCKS, &count);

		for(int i = 0; i < count; ++i)
		{
			char szName[1024];
			glGetActiveUniformBlockName(m_program, i, 1024, 0, szName);

			GLint bytes = 0;
			glGetActiveUniformBlockiv(m_program, i, GL_UNIFORM_BLOCK_DATA_SIZE, &bytes);
			
			OGL4BufferPtr pBuffer = std::make_shared<OGL4Buffer>();
			if(pBuffer->Create(BT_CONSTANT_BUFFER, bytes, nullptr, true) == false)
			{
				pBuffer->Release();
				pBuffer.reset();
				continue;
			}
			UniformBlock block;
			block.index = i;
			block.name = szName;
			block.pBuffer = pBuffer;

			m_uniformBlocks.push_back(block);
		}
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


		CollectUniformBlocks();

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

		BindUniformBlocks();
		BindTextures();
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
	
	OGL4ShaderProgram::ParameterID	OGL4ShaderProgram::FindParameterByName(const char* szName)
	{
		return glGetUniformLocation(m_program, szName);
	}
	OGL4ShaderProgram::ParameterID	OGL4ShaderProgram::FindParameterBlockByName(const char* szName)
	{
		for(uint64 i = 0; i < m_uniformBlocks.size(); ++i)
		{
			if(m_uniformBlocks[i].name == szName)
			{
				return i;
			}
		}
		
		return -1;
	}
	void OGL4ShaderProgram::BindUniformBlocks()
	{
		for(int i = 0; i < m_uniformBlocks.size(); ++i)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, i, m_uniformBlocks[i].pBuffer->GetBufferObject());
			glUniformBlockBinding(m_program, m_uniformBlocks[i].index, i);
		}
	}
	bool OGL4ShaderProgram::SetParameterBlock(ParameterID param, void* data, uint64 bytes)
	{
		if(param < 0 || param >= (int64)m_uniformBlocks.size())
		{
			return false;
		}

		if(m_uniformBlocks[param].pBuffer->GetBytes() < bytes)
		{
			return false;
		}
		void* pBuffer = m_uniformBlocks[param].pBuffer->Map(MAP_DEFAULT);
		memcpy(pBuffer, data, bytes);
		m_uniformBlocks[param].pBuffer->Unmap();

		return true;
	}
	void OGL4ShaderProgram::SetParameterMatrix(ParameterID param, const math::Matrix44& value)
	{
		glProgramUniformMatrix4fv(m_program, (GLint)param, 1, false, value.m);
	}
	void OGL4ShaderProgram::SetParameterFloat(ParameterID param, float value)
	{
		glProgramUniform1f(m_program, (GLint)param, value);
	}
	void OGL4ShaderProgram::SetParameterInt(ParameterID param, int32 value)
	{
		glProgramUniform1i(m_program, (GLint)param, value);
	}
	void OGL4ShaderProgram::SetParameterUInt(ParameterID param, uint32 value)
	{
		glProgramUniform1ui(m_program, (GLint)param, value);
	}
	void OGL4ShaderProgram::SetParameterBool(ParameterID param, bool value)
	{
		glProgramUniform1ui(m_program, (GLint)param, (uint32)value);
	}

	void OGL4ShaderProgram::SetParameterVector(ParameterID param, const math::Vector2& value)
	{
		glProgramUniform2fv(m_program, (GLint)param, 1, value.v);
	}
	void OGL4ShaderProgram::SetParameterVector(ParameterID param, const math::Vector3& value)
	{
		glProgramUniform3fv(m_program, (GLint)param, 1, value.v);
	}
	void OGL4ShaderProgram::SetParameterVector(ParameterID param, const math::Vector4& value)
	{
		glProgramUniform4fv(m_program, (GLint)param, 1, value.v);
	}
	void OGL4ShaderProgram::SetParameterTexture(ParameterID param, Texture2Ptr pTex)
	{
		for(auto& v : m_texLinks)
		{
			if(v.index == param)
			{
				v.pTex = pTex;
				return;
			}
		}

		TextureLink link;
		link.index = (GLuint)param;
		link.pTex = pTex;

		m_texLinks.push_back(link);
	}
	void OGL4ShaderProgram::BindTextures()
	{
		int slot = 0;
		for(auto v : m_texLinks)
		{
			if(v.pTex == nullptr)
			{
				continue;
			}

			glActiveTexture(GL_TEXTURE0 + slot);
			
			OGL4Texture* pGLTex = (OGL4Texture*)v.pTex.get();

			GLenum target = OGL4Convert::TexTypeToGLTarget(pGLTex->GetType());
			glBindTexture(target, pGLTex->GetTextureObject());

			OGL4Sampler* pSampler = (OGL4Sampler*)pGLTex->GetSampler().get();

			if(pSampler == nullptr)
			{
				pSampler = (OGL4Sampler*)v.pSampler.get();
			}

			glBindSampler(slot, pSampler ? pSampler->GetSamplerObject() : 0);
			
			glProgramUniform1i(m_program, v.index, slot);
		}
	}
	void OGL4ShaderProgram::SetParameterSampler(ParameterID param, SamplerStatePtr pSampler)
	{
		for(auto& v : m_texLinks)
		{
			if(v.index == param)
			{
				v.pSampler = pSampler;
				return;
			}
		}

		TextureLink link;
		link.index = (GLuint)param;
		link.pTex = nullptr;
		link.pSampler = pSampler;

		m_texLinks.push_back(link);
	}
}

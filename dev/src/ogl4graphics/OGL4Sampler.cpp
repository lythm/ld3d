#include "ogl4graphics_pch.h"
#include "OGL4Sampler.h"
#include "OGL4Convert.h"


namespace ld3d
{

	OGL4Sampler::OGL4Sampler(void)
	{
		m_sampler = 0;
	}


	OGL4Sampler::~OGL4Sampler(void)
	{
	}
	bool OGL4Sampler::Create()
	{
		glGenSamplers(1, &m_sampler);
		return true;
	}
	void OGL4Sampler::Release()
	{
		glDeleteSamplers(1, &m_sampler);
		m_sampler = 0;
	}

	GLuint OGL4Sampler::GetSamplerObject()
	{
		return m_sampler;
	}

	void OGL4Sampler::SetCompareFunction(COMPARE_FUNC value)
	{
		switch(value)
		{
		case CF_LEQUAL:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
			break;
		case CF_GEQUAL:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_GEQUAL);
			break;
		case CF_LESS:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
			break;
		case CF_GREATER:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_GREATER);
			break;
		case CF_EQUAL:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_EQUAL);
			break;
		case CF_NOTEQUAL:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_NOTEQUAL);
			break;
		case CF_ALWAYS:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_ALWAYS);
			break;
		case CF_NEVER:
			glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GL_NEVER);
			break;
		default:
			assert(0);
			break;
		}
	}

	void OGL4Sampler::SetLod(float minLod, float maxLod)
	{
		glSamplerParameterf(m_sampler, GL_TEXTURE_MIN_LOD, minLod);
		glSamplerParameterf(m_sampler, GL_TEXTURE_MAX_LOD, minLod);
	}
	void OGL4Sampler::SetMipLodBias(int bias)
	{
		glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_MODE, bias);
	}
	void OGL4Sampler::SetBorderColor(const math::Color4& clr)
	{
		glSamplerParameterfv(m_sampler, GL_TEXTURE_BORDER_COLOR, clr.v);
	}
	void OGL4Sampler::SetFilter(FILTER f)
	{
		switch(f)
		{
		case FILTER_MIN_MAG_MIP_POINT:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;

		case FILTER_MIN_MAG_POINT_MIP_LINEAR:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			break;
		case FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;
		case FILTER_MIN_POINT_MAG_MIP_LINEAR:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			break;
		case FILTER_MIN_LINEAR_MAG_MIP_POINT:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			break;
		case FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		case FILTER_MIN_MAG_LINEAR_MIP_POINT:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			break;
		case FILTER_MIN_MAG_MIP_LINEAR:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		case FILTER_ANISOTROPIC:
			glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		default:
			assert(0);
			break;
		}
	}
	void OGL4Sampler::SetAddressMode(ADDRESS_MODE u, ADDRESS_MODE v, ADDRESS_MODE w)
	{
		glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, AddressModeToGL(u));
		glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, AddressModeToGL(v));
		glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, AddressModeToGL(w));
	}
	void OGL4Sampler::SetMaxAnisotropy(uint32 value)
	{
		//float num = 0;
		//glGetFloatv(GL_MAX_TEXTURE_AN
		//glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY​, &num);
	}
	GLenum OGL4Sampler::AddressModeToGL(ADDRESS_MODE mode)
	{
		switch(mode)
		{
		case AM_REPEAT:
			return GL_REPEAT;
		case AM_MIRROR:
			return GL_MIRRORED_REPEAT;
		case AM_CLAMP:
			return GL_CLAMP_TO_EDGE;
		case AM_BORDER:
			return GL_CLAMP_TO_BORDER;
		default:
			assert(0);
			break;
		}

		return GL_INVALID_ENUM;
	}
}

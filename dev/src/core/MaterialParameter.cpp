#include "core_pch.h"
#include "..\..\include\core\MaterialParameter.h"

namespace ld3d
{
	MaterialParameter::MaterialParameter(const std::string& name, const std::vector<ParamInfo>& params)
	{
		m_name = name;
		m_params = params;
	}


	MaterialParameter::~MaterialParameter(void)
	{

	}
	const std::string& MaterialParameter::GetName()
	{
		return m_name;
	}
	bool MaterialParameter::SetParameterBlock(void* data, uint64 bytes)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterBlock(v.second, data, bytes);
		}
		return true;
	}
	void MaterialParameter::SetParameterMatrix(const math::Matrix44& value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterMatrix(v.second, value);
		}
	}
	void MaterialParameter::SetParameterFloat(float value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterFloat(v.second, value);
		}
	}
	void MaterialParameter::SetParameterInt(int32 value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterInt(v.second, value);
		}
	}
	void MaterialParameter::SetParameterUInt(uint32 value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterUInt(v.second, value);
		}
	}
	void MaterialParameter::SetParameterBool(bool value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterBool(v.second, value);
		}
	}
	void MaterialParameter::SetParameterVector(const math::Vector2& value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterVector(v.second, value);
		}
	}
	void MaterialParameter::SetParameterVector(const math::Vector3& value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterVector(v.second, value);
		}
	}
	void MaterialParameter::SetParameterVector(const math::Vector4& value)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterVector(v.second, value);
		}
	}
	void MaterialParameter::SetParameterTexture(Texture2Ptr pTex)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterTexture(v.second, pTex);
		}
	}
	void MaterialParameter::SetParameterSampler(SamplerStatePtr pSampler)
	{
		for(auto v : m_params)
		{
			v.first->SetParameterSampler(v.second, pSampler);
		}
	}
}

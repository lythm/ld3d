#include "core_pch.h"
#include "core/MaterialTech.h"
#include "core/MaterialPass.h"

namespace ld3d
{
	MaterialTech::MaterialTech(const std::string& name)
	{
		m_name = name;
		m_valid = true;
	}


	MaterialTech::~MaterialTech(void)
	{
	}

	uint32 MaterialTech::GetPassCount()
	{
		return (uint32)m_passes.size();
	}
	void MaterialTech::Release()
	{
		for(size_t i = 0; i < m_passes.size(); ++i)
		{
			m_passes[i]->Release();
		}
		m_passes.clear();
	}
	MaterialPassPtr MaterialTech::GetPassByIndex(uint32 index)
	{
		return m_passes[index];
	}
	void MaterialTech::AddPass(MaterialPassPtr pPass)
	{
		m_passes.push_back(pPass);
	}
	const std::string& MaterialTech::GetName()
	{
		return m_name;
	}
	bool MaterialTech::Validate()
	{
		m_valid = false;
		for(size_t i = 0; i < m_passes.size(); ++i)
		{
			if(m_passes[i]->Validate() == false)
			{
				return false;
			}
		}

		m_valid = true;
		return true;
	}
	bool MaterialTech::IsValid()
	{
		return m_valid;
	}
}

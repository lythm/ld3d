#include "core_pch.h"
#include "MaterialParameterManager.h"
#include "core\MaterialParameter.h"
namespace ld3d
{
	MaterialParameterManager::MaterialParameterManager(void)
	{
	}


	MaterialParameterManager::~MaterialParameterManager(void)
	{
		m_parameterMap.clear();
		m_params.clear();
	}
	bool MaterialParameterManager::AddParameter(MaterialParameterPtr pParam)
	{
		if(Exist(pParam->GetName()))
		{
			return false;
		}

		m_params.push_back(pParam);
		m_parameterMap[pParam->GetName()] = pParam;

		return true;

	}
	bool MaterialParameterManager::Exist(const std::string& name)
	{
		return m_parameterMap.find(name) != m_parameterMap.end();
	}

	uint32 MaterialParameterManager::GetParameterCount()
	{
		return (uint32)m_params.size();
	}
	MaterialParameterPtr MaterialParameterManager::GetParameterByIndex(uint32 index)
	{
		return m_params[index];
	}
	MaterialParameterPtr MaterialParameterManager::GetParameterByName(const std::string& name)
	{
		if(Exist(name) == false)
		{
			return MaterialParameterPtr();
		}
		return m_parameterMap[name];
	}
}

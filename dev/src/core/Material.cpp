#include "core_pch.h"
#include "core/Material.h"
#include "core_utils.h"
#include "MaterialParameterManager.h"
#include "core/MaterialTech.h"
#include "core/MaterialPass.h"
#include "core/MaterialParameter.h"

namespace ld3d
{
	Material::Material(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;

		m_pParamManager = std::make_shared<MaterialParameterManager>();
	}


	Material::~Material(void)
	{
	}
	
	void Material::Release()
	{
		m_pParamManager.reset();

		for(size_t i = 0; i < m_techs.size(); ++i)
		{
			m_techs[i]->Release();
		}
		m_techs.clear();
		m_pCurrentTech.reset();
	}
	uint32 Material::Begin()
	{
		if(m_pCurrentTech == nullptr)
		{
			return 0;
		}
		return m_pCurrentTech->GetPassCount();
	}
	void Material::ApplyPass(uint32 index)
	{
		MaterialPassPtr pPass = m_pCurrentTech->GetPassByIndex(index);
		
		pPass->Apply();
	}
	void Material::End()
	{
	}
	MaterialParameterPtr Material::GetParameterByName(const char* szName)
	{
		MaterialParameterPtr pParam = m_pParamManager->GetParameterByName(szName);
		if(pParam)
		{
			return pParam;
		}

		std::vector<MaterialParameter::ParamInfo> params;

		for(size_t i = 0; i < m_techs.size(); ++i)
		{
			for(size_t ii = 0; ii < m_techs[i]->GetPassCount(); ++ii)
			{
				MaterialPassPtr pPass = m_techs[i]->GetPassByIndex((uint32)ii);
				ShaderProgramPtr pProgram = pPass->GetProgram();

				ShaderProgram::ParameterID id = pProgram->FindParameterByName(szName);
				if(id >= 0)
				{
					params.push_back(MaterialParameter::ParamInfo(pProgram, id));
					continue;
				}

				id = pProgram->FindParameterBlockByName(szName);
				if(id >= 0)
				{
					params.push_back(MaterialParameter::ParamInfo(pProgram, id));
					continue;
				}
			}
		}

		if(params.size() == 0)
		{
			return nullptr;
		}

		pParam = std::make_shared<MaterialParameter>(szName, params);
		m_pParamManager->AddParameter(pParam);

		return pParam;
	}
	
	bool Material::SetCurrentTech(const char* szName)
	{
		MaterialTechPtr pFind = GetTechByName(szName);
		if(pFind == nullptr)
		{
			return false;
		}
		m_pCurrentTech = pFind;

		return true;
	}
	MaterialTechPtr Material::GetTechByName(const char* szName)
	{
		for(size_t i = 0; i < m_techs.size(); ++i)
		{
			if(m_techs[i]->GetName() == szName)
			{
				return m_techs[i];
			}
		}

		return MaterialTechPtr();
	}
	uint32 Material::GetTechCount()
	{
		return (uint32)m_techs.size();
	}
	MaterialTechPtr Material::GetTechByIndex(uint32 index)
	{
		return m_techs[index];
	}
	void Material::AddTech(MaterialTechPtr pTech)
	{
		if(pTech == nullptr)
		{
			return;
		}
		m_techs.push_back(pTech);

		if(m_pCurrentTech == nullptr)
		{
			m_pCurrentTech = pTech;
		}
	}
}

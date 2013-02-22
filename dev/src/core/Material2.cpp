#include "core_pch.h"
#include "..\..\include\core\Material2.h"
#include "core_utils.h"
#include "MaterialParameterManager.h"
#include "core\MaterialTech.h"
#include "core\MaterialPass.h"

namespace ld3d
{
	Material2::Material2(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;

		m_pParamManager = alloc_object<MaterialParameterManager>();
	}


	Material2::~Material2(void)
	{
	}
	bool Material2::LoadFromFile(const char* szFile)
	{
		TiXmlDocument doc;

		if(doc.LoadFile(szFile) == false)
		{
			return false;
		}



		return true;
	}
	void Material2::Release()
	{
		m_pParamManager.reset();

		for(size_t i = 0; i < m_techs.size(); ++i)
		{
			m_techs[i]->Release();
		}
		m_techs.clear();
	}
	uint32 Material2::Begin()
	{
		if(m_pCurrentTech == nullptr)
		{
			return 0;
		}
		return m_pCurrentTech->GetPassCount();
	}
	void Material2::ApplyPass(uint32 index)
	{
		MaterialPassPtr pPass = m_pCurrentTech->GetPassByIndex(index);
		
		pPass->Apply();
	}
	void Material2::End()
	{
	}
	MaterialParameterPtr Material2::GetParameterByName(const char* szName)
	{
		return m_pParamManager->GetParameterByName(szName);
	}
	uint32 Material2::GetParameterCount()
	{
		return m_pParamManager->GetParameterCount();
	}
	MaterialParameterPtr Material2::GetPatameterByIndex(uint32 index)
	{
		return m_pParamManager->GetParameterByIndex(index);
	}
	bool Material2::SelectTechByName(const char* szName)
	{
		MaterialTechPtr pFind = GetTechByName(szName);
		if(pFind == nullptr)
		{
			return false;
		}
		m_pCurrentTech = pFind;

		return true;
	}
	MaterialTechPtr Material2::GetTechByName(const char* szName)
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
	uint32 Material2::GetTechCount()
	{
		return (uint32)m_techs.size();
	}
	MaterialTechPtr Material2::GetTechByIndex(uint32 index)
	{
		return m_techs[index];
	}
}

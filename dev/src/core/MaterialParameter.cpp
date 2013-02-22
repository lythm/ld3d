#include "core_pch.h"
#include "..\..\include\core\MaterialParameter.h"

namespace ld3d
{
	MaterialParameter::MaterialParameter(const std::string& name)
	{
		m_name = name;
	}


	MaterialParameter::~MaterialParameter(void)
	{

	}
	const std::string& MaterialParameter::GetName()
	{
		return m_name;
	}
	
}

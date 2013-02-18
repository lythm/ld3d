#include "core_pch.h"
#include "..\..\include\core\Material2.h"

namespace ld3d
{
	Material2::Material2(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;
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

	}
	void Material2::Begin()
	{
	}
	void Material2::ApplyPass()
	{
	}
	void Material2::End()
	{
	}
}

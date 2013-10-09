#include "core_ext_pch.h"
#include "Impl_WorldMeshRenderer.h"



#include "CorePackage.h"

namespace ld3d
{

	Impl_WorldMeshRenderer::Impl_WorldMeshRenderer(GameObjectManagerPtr pManager) : WorldMeshRenderer(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_WorldMeshRenderer::~Impl_WorldMeshRenderer(void)
	{
	}
}


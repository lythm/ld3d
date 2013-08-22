#include "core_ext_pch.h"
#include "core/ext/WorldMeshRenderer.h"
#include "CorePackage.h"

namespace ld3d
{

	WorldMeshRenderer::WorldMeshRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("WorldMeshRenderer", pManager)
	{
		SetVersion(g_packageVersion);
	}


	WorldMeshRenderer::~WorldMeshRenderer(void)
	{
	}
}


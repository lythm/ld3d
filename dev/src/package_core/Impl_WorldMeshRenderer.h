#pragma once

#include "packages/core/WorldMeshRenderer.h"

namespace ld3d
{

	class Impl_WorldMeshRenderer : public WorldMeshRenderer
	{
	public:
		Impl_WorldMeshRenderer(GameObjectManagerPtr pManager);
		virtual ~Impl_WorldMeshRenderer(void);

	};

}
#pragma once

#include "core/GameObjectComponent.h"
#include "core/RenderData.h"
#include "core/g_format.h"
#include "core/VertexFormat.h"

namespace ld3d
{

	class MeshRenderer : public GameObjectComponent
	{
	public:
		MeshRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("MeshRenderer", pManager){}
		virtual ~MeshRenderer(void){}

		virtual const bool&												IsDeferred()										= 0;
		virtual void													SetDeferred(const bool& b)							= 0;;

	};
}

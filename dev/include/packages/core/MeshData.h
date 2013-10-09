#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class MeshData : public GameObjectComponent
	{
	public:
		MeshData(GameObjectManagerPtr pManager) : GameObjectComponent("MeshData", pManager){}
		virtual ~MeshData(void){}

		virtual MeshPtr						GetMesh()												= 0;
		virtual void						SetMesh(MeshPtr pMesh)									= 0;
		
		virtual bool						SetMeshAsset(const std::string& asset)					= 0;
		virtual const std::string&			GetMeshAsset()											= 0;

	};
}

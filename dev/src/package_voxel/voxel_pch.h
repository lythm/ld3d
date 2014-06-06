#pragma once

#include "core/core_all.h"
#include "packages/voxel/voxel_ptr.h"

#include "packages/voxel/VoxelType.h"



namespace ld3d
{
	extern Version											g_packageVersion;

	class VoxelWorldMaterialManager;
	class VoxelWorldImpl;


	typedef std::shared_ptr<VoxelWorldImpl>					VoxelWorldImplPtr;
	typedef std::shared_ptr<VoxelWorldMaterialManager>		VoxelWorldMaterialManagerPtr;


	GameObjectManagerPtr									GetManager();

}

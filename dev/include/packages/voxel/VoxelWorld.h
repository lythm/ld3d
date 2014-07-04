#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class VoxelWorld : public GameObjectComponent
	{
	public:

		

		virtual const int&									GetVoxelSize()								= 0;
		virtual void										SetVoxelSize(const int& size)				= 0;

		virtual const int&									GetWorldSizeY()								= 0;
		virtual void										SetWorldSizeY(const int& y)					= 0;

		virtual const int&									GetWorldSizeX()								= 0;
		virtual void										SetWorldSizeX(const int& x)					= 0;

		virtual const int&									GetWorldSizeZ()								= 0;
		virtual void										SetWorldSizeZ(const int& z)					= 0;

		virtual uint32										GetLoadingQueueSize()						= 0;
		virtual uint32										GetChunkCount(){return 0;}
		virtual int32										GetFaceCount(){return 0;}
		virtual int32										GetNonEmptyChunkCount(){return 0;}
	protected:
		VoxelWorld(GameObjectManagerPtr pManager) : GameObjectComponent("Voxel.World", pManager){}
		virtual ~VoxelWorld(void){}
	};
}

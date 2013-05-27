#pragma once

#include <boost\smart_ptr.hpp>

namespace ld3d
{
	class Voxel;
	class VoxelWorld;
	class VoxelWorldRenderer;
	class VoxelObject;
	class VoxelObjectRenderer;
	class VoxelPolygonizer;


	typedef boost::shared_ptr<Voxel>								VoxelPtr;
	typedef boost::shared_ptr<VoxelPolygonizer>						VoxelPolygonizerPtr;
	typedef boost::shared_ptr<VoxelWorld>							VoxelWorldPtr;
	typedef boost::shared_ptr<VoxelWorldRenderer>					VoxelWorldRendererPtr;
	typedef boost::shared_ptr<VoxelObject>							VoxelObjectPtr;
	typedef boost::shared_ptr<VoxelObjectRenderer>					VoxelObjectRendererPtr;

	class VoxelWorldRenderData;
	class VoxelBlock;

	typedef boost::shared_ptr<VoxelBlock>							VoxelBlockPtr;
	typedef boost::shared_ptr<VoxelWorldRenderData>					VoxelWorldRenderDataPtr;
		
}

#pragma once

#include <boost\smart_ptr.hpp>

namespace ld3d
{
	class VoxelWorld;
	class VoxelWorldRenderer;
	class VoxelObject;
	class VoxelObjectRenderer;
	class VoxelPolygonizer;
	class VoxelPool;


	typedef boost::shared_ptr<VoxelPool>							VoxelPoolPtr;
	typedef boost::shared_ptr<VoxelPolygonizer>						VoxelPolygonizerPtr;
	typedef boost::shared_ptr<VoxelWorld>							VoxelWorldPtr;
	typedef boost::shared_ptr<VoxelWorldRenderer>					VoxelWorldRendererPtr;
	typedef boost::shared_ptr<VoxelObject>							VoxelObjectPtr;
	typedef boost::shared_ptr<VoxelObjectRenderer>					VoxelObjectRendererPtr;

	class VoxelWorldRenderData;
	
	typedef boost::shared_ptr<VoxelWorldRenderData>					VoxelWorldRenderDataPtr;
		
}

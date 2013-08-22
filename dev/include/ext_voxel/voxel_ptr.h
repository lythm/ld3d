#pragma once

#include <boost/smart_ptr.hpp>

namespace ld3d
{
	class VoxelWorld;
	class VoxelWorldRenderer;
	class VoxelObject;
	class VoxelObjectRenderer;
	class VoxelPolygonizer;
	class VoxelPool;
	class VoxelWorldDataSet;
	class VoxelWorldOctTree;
	class VoxelWorldGenerator;

	typedef std::shared_ptr<VoxelWorldGenerator>					VoxelWorldGeneratorPtr;
	typedef std::shared_ptr<VoxelWorldOctTree>					VoxelWorldOctTreePtr;
	typedef std::shared_ptr<VoxelWorldDataSet>					VoxelWorldDataSetPtr;
	typedef std::shared_ptr<VoxelPool>							VoxelPoolPtr;
	typedef std::shared_ptr<VoxelPolygonizer>						VoxelPolygonizerPtr;
	typedef std::shared_ptr<VoxelWorld>							VoxelWorldPtr;
	typedef std::shared_ptr<VoxelWorldRenderer>					VoxelWorldRendererPtr;
	typedef std::shared_ptr<VoxelObject>							VoxelObjectPtr;
	typedef std::shared_ptr<VoxelObjectRenderer>					VoxelObjectRendererPtr;

	class VoxelWorldRenderData;
	
	typedef std::shared_ptr<VoxelWorldRenderData>					VoxelWorldRenderDataPtr;
		
}

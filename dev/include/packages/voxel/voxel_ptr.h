#pragma once

#include <boost/smart_ptr.hpp>

namespace ld3d
{
	class VoxelWorld;
	class VoxelWorldRenderer;
	class VoxelObject;
	class VoxelObjectRenderer;
	
	typedef std::shared_ptr<VoxelWorld>								VoxelWorldPtr;
	typedef std::shared_ptr<VoxelWorldRenderer>						VoxelWorldRendererPtr;
	typedef std::shared_ptr<VoxelObject>							VoxelObjectPtr;
	typedef std::shared_ptr<VoxelObjectRenderer>					VoxelObjectRendererPtr;

	
}

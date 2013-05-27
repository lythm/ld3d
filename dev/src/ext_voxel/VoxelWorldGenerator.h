#pragma once

namespace ld3d
{
	class VoxelWorldGenerator
	{
	public:
		
		static std::vector<VoxelBlockPtr>											Generate(Allocator* pAllocator, int w, int h);


	private:

		VoxelWorldGenerator(void);
		virtual ~VoxelWorldGenerator(void);
	};


}
#pragma once

namespace ld3d
{
	class VoxelWorldMesh;
	class VoxelWorldChunk;

	class VoxelWorldUtils
	{
	public:

		struct BlockMaterial
		{
			uint32											type;
			TexturePtr										pTex;
		};


		static std::vector<VoxelWorldMesh>					GenChunkMesh(VoxelWorldChunk* pChunk);


	private:

		VoxelWorldUtils(void){}
		virtual ~VoxelWorldUtils(void){}
	};
}

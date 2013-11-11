#pragma once

namespace ld3d
{
	class VoxelWorldMeshGenerator
	{
	public:

		struct BlockMaterial
		{
			uint32									type;
			TexturePtr								pTex;
		};

		VoxelWorldMeshGenerator(void);
		virtual ~VoxelWorldMeshGenerator(void);

		bool										Initialize();
		void										Release();
	};


}
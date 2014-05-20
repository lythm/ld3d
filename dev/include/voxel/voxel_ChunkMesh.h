#pragma once

namespace ld3d
{
	namespace voxel
	{
		class ChunkMesh
		{
		public:
			ChunkMesh(void);
			virtual ~ChunkMesh(void);

			void											UpdateMesh(WorldPtr pWorld, ChunkPtr pChunk);


		private:

		};


	}
}

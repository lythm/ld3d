#pragma once


namespace ld3d
{
	namespace voxel
	{
		class _DLL_CLASS World
		{
		public:
			World(void);
			virtual ~World(void);

			bool											Initialize(WorldGenPtr pGen);

			void											Release();

		private:
			WorldGenPtr										m_pGen;

			ChunkHashmapPtr									m_pChunkMap;
		};

	}
}


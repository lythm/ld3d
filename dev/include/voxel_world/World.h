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

			bool											Create();
			void											Destroy();


		private:
			WorldGenPtr										m_pGen;

			ChunkHasmapPtr									m_pChunkMap;
		};

	}
}


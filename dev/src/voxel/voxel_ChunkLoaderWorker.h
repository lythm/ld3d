#pragma once

#include "voxel/voxel_ChunkKey.h"
#include "voxel/voxel_ChunkAdjacency.h"
#include "voxel/voxel_ChunkData.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkLoaderWorker
		{
		public:
			enum
			{
				cmd_exit,
				cmd_load_chunk,
				cmd_gen_mesh,
				cmd_unload_chunk,

			};
				
			struct Command
			{
				uint32												id;
				ChunkKey											key;
				ChunkData											chunk_data;
				ChunkAdjacency										chunk_adjacency;
				bool												chunk_empty;
				bool												gen_mesh;
				bool												force_regen;
				ChunkMesh*											mesh;

				std::function<void(const ChunkKey&)>				on_loaded;

			};
			
			typedef boost::lockfree::spsc_queue<Command, boost::lockfree::fixed_sized<true>>		CommandQueue;

			ChunkLoaderWorker(uint16 inQueueSize, uint16 outQueueSize);
			virtual ~ChunkLoaderWorker(void);

			void																					Start();
			void																					Stop();
			void																					Join();
			

			bool																					PushTask(const Command& task);
			bool																					PopTask(Command& task);

			void																					SetWorldGenerator(WorldGenPtr pWorldGen);
			void																					SetMeshizer(MeshizerPtr pMeshizer);
		private:
			void																					_gen_mesh(Command& t);
			void																					_load_chunk(Command& t);
			void																					_run();
		private:
			CommandQueue																			m_in;
			CommandQueue																			m_out;
			MeshizerPtr																				m_pMeshizer;
			boost::thread																			m_thread;
			WorldGenPtr																				m_pGenerator;
		};
	}
}

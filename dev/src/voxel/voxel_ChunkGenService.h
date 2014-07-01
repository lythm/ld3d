#pragma once

#include "voxel/voxel_Meshizer.h"
#include "voxel/voxel_WorldGen.h"
#include "voxel/voxel_ChunkKey.h"
#include "voxel/voxel_ChunkAdjacency.h"
#include "voxel/voxel_ChunkData.h"

namespace ld3d
{
	namespace voxel
	{
		class ChunkGenService
		{
			
		public:

			struct Message
			{
				enum
				{
					message_exit,
					message_gen_chunk,
					message_gen_mesh,
				};
				uint32														id;
			};

			struct Message_Exit : public Message
			{
				Message_Exit()
				{
					id				= message_exit;
				}

			};
			struct Message_GenChunk : public Message
			{
				Message_GenChunk(const ChunkKey& _key)
				{
					id				= message_gen_chunk;
					chunk_empty		= false;
					key				= _key;
					chunk_adjacency = ChunkAdjacency(key);

				}
				ChunkKey													key;
				ChunkData													chunk_data;
				ChunkAdjacency												chunk_adjacency;
				bool														chunk_empty;

				std::function<void (const ChunkKey&, 
					const ChunkData&,
					const ChunkAdjacency&,
					bool)>													on_completed;
			};
			struct Message_GenMesh : public Message
			{
				Message_GenMesh(const ChunkKey& _key)
				{
					id				= message_gen_mesh;
					key				= _key;
					mesh			= nullptr;
				}

				ChunkKey													key;
				ChunkData													chunk_data;
				ChunkAdjacency												chunk_adjacency;
				ChunkMesh*													mesh;

				std::function<void(const ChunkKey&,
					ChunkMesh*)>											on_completed;
			};


			typedef boost::lockfree::queue<Message*, boost::lockfree::capacity<65535>>						MessageQueue;


			struct worker
			{
				worker(MessageQueue* in, MessageQueue* out, const Meshizer& meshizer, const WorldGen& worldGen)
				{
					m_in				= in;
					m_out				= out;
					m_meshizer			= meshizer;
					m_worldGen			= worldGen;

				}
				void operator()();

				worker(const worker& other)
				{
					m_in				= other.m_in;
					m_out				= other.m_out;
					m_meshizer			= other.m_meshizer;
					m_worldGen			= other.m_worldGen;
				}

				MessageQueue*												m_in;
				MessageQueue*												m_out;

				Meshizer													m_meshizer;
				WorldGen													m_worldGen;
			};


			ChunkGenService(void);
			virtual ~ChunkGenService(void);

		
			bool															Initialize(const Meshizer& meshizer, const WorldGen& worldGen);
			void															Release();
			void															Run();


			void															GenChunk(const ChunkKey& key, 
																				const std::function<void (const ChunkKey&, 
																					const ChunkData&,
																					const ChunkAdjacency&,
																					bool)>& on_completed);

			void															GenMesh(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, 
																				const std::function<void(const ChunkKey&,
																					ChunkMesh*)>& on_complete);
		private:
			void															PushMessage(Message* msg);
			
			void															HandleMessage(Message* msg);
		private:

			MessageQueue													m_in;
			MessageQueue													m_out;

			boost::thread_group												m_workers;
		};
	}
}

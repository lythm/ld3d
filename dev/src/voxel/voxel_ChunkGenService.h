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
				}
				ChunkKey													key;
				ChunkData													chunk_data;
				ChunkAdjacency												chunk_adjacency;
				bool														chunk_empty;
			};
			struct Message_GenMesh : public Message
			{
				Message_GenMesh()
				{
					id				= message_gen_mesh;
				}

				ChunkKey													key;
				ChunkData													chunk_data;
				ChunkAdjacency												chunk_adjacency;
				ChunkMesh*													mesh;

			};


			typedef boost::lockfree::queue<Message*, 
				boost::lockfree::capacity<5000>>							MessageQueue;


			struct worker
			{
				worker(MessageQueue* in, MessageQueue* out, const Meshizer& meshizer, const WorldGen& worldGen)
				{
					m_in				= in;
					m_out				= out;
					m_meshizer			= m_meshizer;
					m_worldGen			= m_worldGen;

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


			void															GenChunk(const ChunkKey& key);
		private:

			void															PostMessage(Message* msg);
			void															HandleMessage(Message* msg);
		private:

			MessageQueue													m_in;
			MessageQueue													m_out;

			boost::thread_group												m_workers;

			std::list<Message*>												m_tmpList;

		};
	}
}

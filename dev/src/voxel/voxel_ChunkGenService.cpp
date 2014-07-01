#include "voxel_pch.h"
#include "voxel_ChunkGenService.h"
#include "voxel_VoxelUtils.h"
#include "voxel/voxel_ChunkMesh.h"

namespace ld3d
{
	namespace voxel
	{
		void ChunkGenService::worker::operator()()
		{
			Message* msg = nullptr;
			while(true)
			{
				while(m_in->pop(msg) == false)
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
				}

				switch(msg->id)
				{
				case Message::message_exit:

					// do not free msg, allocator is not thread safe
					return;
				case Message::message_gen_mesh:
					{
						Message_GenMesh* gen_mesh = (Message_GenMesh*)msg;

						Coord chunk_origin = gen_mesh->key.ToChunkOrigin();
						Coord region_origin = VoxelUtils::ToRegionOrigin(chunk_origin);
			
						Coord chunk_mesh_base = chunk_origin - region_origin;


						m_meshizer.GenerateMesh(gen_mesh->key, gen_mesh->chunk_data, gen_mesh->chunk_adjacency, chunk_mesh_base, gen_mesh->mesh);

						while(false == m_out->push(gen_mesh))
						{
							boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
						}
					}
					break;

				case Message::message_gen_chunk:
					{
						Message_GenChunk* gen_chunk = (Message_GenChunk*)msg;
						gen_chunk->chunk_empty = !m_worldGen.GenChunk(gen_chunk->key, gen_chunk->chunk_data, gen_chunk->chunk_adjacency);

						while(false == m_out->push(gen_chunk))
						{
							boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
						}
					}
					break;
				default:
					break;
				}
			}
		}
		
		ChunkGenService::ChunkGenService(void)// : m_in(65535), m_out(65535)
		{
		}
		
		ChunkGenService::~ChunkGenService(void)
		{
		}
		bool ChunkGenService::Initialize(const Meshizer& meshizer, const WorldGen& worldGen)
		{
			
			int num_thread = 2;
			for(int i = 0; i < num_thread; ++i)
			{
				m_workers.create_thread(worker(&m_in, &m_out, meshizer, worldGen));
			}
			return true;
		}
		void ChunkGenService::Release()
		{
			for(int i =0; i < m_workers.size(); ++i)
			{
				Message_Exit *m = alloc_object_rawptr<Message_Exit>(allocator());

				PushMessage(m);
			}
			m_workers.join_all();
		}
		void ChunkGenService::HandleMessage(Message* msg)
		{
			switch(msg->id)
			{
			case Message::message_gen_chunk:
				{
					Message_GenChunk* gen_chunk = (Message_GenChunk*)msg;
					if(gen_chunk->on_completed)
					{
						gen_chunk->on_completed(gen_chunk->key, gen_chunk->chunk_data, gen_chunk->chunk_adjacency, gen_chunk->chunk_empty);
					}

					free_object(allocator(), gen_chunk);
				}
				break;
			case Message::message_gen_mesh:
				{
					Message_GenMesh* gen_mesh = (Message_GenMesh*)msg;

					if(gen_mesh->on_completed)
					{
						gen_mesh->on_completed(gen_mesh->key, gen_mesh->mesh);
					}


					gen_mesh->mesh->Release();
					free_object(allocator(), gen_mesh->mesh);
					free_object(allocator(), gen_mesh);
				}
				break;
			default:
				break;
			}
		}
		
		void ChunkGenService::Run()
		{
			Message* msg = nullptr;

			while(m_out.pop(msg) == true)
			{
				HandleMessage(msg);
			}
		}
		void ChunkGenService::GenChunk(const ChunkKey& key, const std::function<void (const ChunkKey&, const ChunkData&, const ChunkAdjacency&, bool)>& on_completed)
		{
			Message_GenChunk* msg = alloc_object_rawptr<Message_GenChunk>(allocator(), key);
			msg->on_completed = on_completed;
			PushMessage(msg);
		}
		void ChunkGenService::GenMesh(const ChunkKey& key, const ChunkData& chunk_data, const ChunkAdjacency& adj, const std::function<void(const ChunkKey&, ChunkMesh*)>& on_complete)
		{
			Message_GenMesh* msg = alloc_object_rawptr<Message_GenMesh>(allocator(), key);
			msg->chunk_adjacency = adj;
			msg->chunk_data = chunk_data;
			msg->mesh = alloc_object_rawptr<ChunkMesh>(allocator());
			msg->on_completed = on_complete;
			PushMessage(msg);
		}
		void ChunkGenService::PushMessage(Message* msg)
		{
			if(false == m_in.push(msg))
			{
				logger() << "[ChunkGenService]: failed to post message.\n";
			}
		}
	}
}

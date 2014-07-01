#include "voxel_pch.h"
#include "voxel_ChunkGenService.h"

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

					break;
				default:
					break;
				}
			}
		}
		
		ChunkGenService::ChunkGenService(void)
		{
		}
		
		ChunkGenService::~ChunkGenService(void)
		{
		}
		bool ChunkGenService::Initialize(const Meshizer& meshizer, const WorldGen& worldGen)
		{
			int num_thread = 4;
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

				PostMessage(m);
			}
			m_workers.join_all();
		}
		void ChunkGenService::HandleMessage(Message* msg)
		{

		}
		void ChunkGenService::PostMessage(Message* msg)
		{
			while(m_in.push(msg) == false)
			{
				Message* tmp_msg = nullptr;

				while(m_out.pop(tmp_msg))
				{
					m_tmpList.push_back(tmp_msg);
				}

				boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
			}
		}
		void ChunkGenService::Run()
		{
			std::list<Message*> tmp_list = m_tmpList;
			for(auto i = tmp_list.begin(); i != tmp_list.end(); ++i)
			{
				HandleMessage(*i);
			}
			
			Message* msg = nullptr;

			while(m_out.pop(msg) == true)
			{
				HandleMessage(msg);
			}
		}
		void ChunkGenService::GenChunk(const ChunkKey& key)
		{
			Message_GenChunk* msg = alloc_object_rawptr<Message_GenChunk>(allocator(), key);

			PostMessage(msg);
		}
	}
}

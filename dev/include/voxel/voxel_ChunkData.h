#pragma once


namespace ld3d
{
	namespace voxel
	{
		class ChunkData
		{
		public:
			ChunkData(uint8* data = nullptr)
			{
				if(data == nullptr)
				{
					memset(m_data, 0, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);

				}
				else
				{
					CopyData(data);
				}
				
			}
			~ChunkData(void)
			{
			}
			static uint32									ToIndex(uint32 x, uint32 y, uint32 z)
			{
				uint32 index = y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x;
				return index;
			}



			uint8											Get(uint32 x, uint32 y, uint32 z) const
			{
				uint32 index = ToIndex(x, y, z);
				return m_data[index];
			}
			
			void											Set(uint32 x, uint32 y, uint32 z, uint8 val)
			{
				uint32 index	= ToIndex(x, y, z);
				m_data[index]	= val;

			}
			
			uint8*											GetData() const
			{
				return (uint8*)m_data;
			}
			void											CopyData(uint8* data)
			{
				memcpy(m_data, data, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			}

			void											Fill(uint8 val)
			{
				memset(m_data, val, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
			}
		private:
			uint8											m_data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
		};


	}
}
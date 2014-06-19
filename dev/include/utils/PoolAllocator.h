#pragma once

#include "utils/Allocator.h"
#include <vector>

namespace ld3d
{
	class PoolAllocator : public Allocator
	{
		struct pool_allocator
		{
			typedef std::size_t							size_type;

			typedef std::ptrdiff_t						difference_type;

			static char * malloc(const size_type bytes)
			{
				return static_cast<char *>((std::malloc)(bytes));
			}
			static void free(char * const block)
			{
				(std::free)(block);
			}
		};
		struct _MemBlock
		{
			uint64										bytes;
			uint8										data[];
		};

		typedef boost::pool<pool_allocator>				Pool_T;

	public:
		
		PoolAllocator(void);
		virtual ~PoolAllocator(void);

		void*											Alloc(uint64 bytes);
		void											Free(void* mem);

		bool											Initialize();
		void											Release();

		void											Update();

		uint64											GetAllocatedBytes();
	private:
		
		
		int64											m_allocBytes;
		
		std::vector<Pool_T*>							m_pools;
	};


}
#pragma once

#include "core/Allocator.h"

namespace ld3d
{
	class _DLL_CLASS PoolAllocator : public Allocator
	{
		typedef std::shared_ptr<MemPool>				MemPoolPtr;
	public:
		PoolAllocator(void);
		virtual ~PoolAllocator(void);

		void*											Alloc(uint64 bytes);
		void											Free(void* mem);

		bool											Initialize();
		void											Release();

		void											Update();

		uint64											GetTotalBytes();
		uint64											GetBytesLeft();
	private:
		MemPoolPtr										m_pMemPool;
        
        
        struct pool_allocator
        {
            typedef std::size_t size_type;
            
            typedef std::ptrdiff_t difference_type;
            
            static char * malloc(const size_type bytes)
            {
                return static_cast<char *>((std::malloc)(bytes));
            }
            static void free(char * const block)
            {
                (std::free)(block);
            }
            
            
        };
        
        std::vector<boost::pool<pool_allocator>>		m_pools;
	};


}
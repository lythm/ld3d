#pragma once

#include "utils/Allocator.h"

namespace ld3d
{
	class StdAllocator : public Allocator
	{
	public:
		StdAllocator(void);
		virtual ~StdAllocator(void);

		void*								Alloc(uint64 bytes);
		void								Free(void* mem);
		uint64								GetAllocatedBytes(){return 0;}
	private:
		
	};
}
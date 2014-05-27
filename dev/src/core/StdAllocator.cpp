#include "core_pch.h"
#include "core/StdAllocator.h"

namespace ld3d
{
	StdAllocator::StdAllocator(void)
	{
	}


	StdAllocator::~StdAllocator(void)
	{
	}
	void* StdAllocator::Alloc(uint64 bytes)
	{
		return new uint8[bytes];
	}
	void StdAllocator::Free(void* mem)
	{
		delete mem;
	}
	uint64 StdAllocator::GetTotalBytes()
	{
		return 0;
	}
	uint64 StdAllocator::GetBytesLeft()
	{
		return 0;
	}
}

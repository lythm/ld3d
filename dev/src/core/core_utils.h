#pragma once

#include "core\CoreApi.h"
#include "core\Allocator.h"

namespace ld3d
{
	inline
		void*												mem_alloc(uint64 bytes)
	{
		return CoreApi::GetAllocator()->Alloc(bytes);
	}
	inline
		void												mem_free(void* pMem)
	{
		CoreApi::GetAllocator()->Free(pMem);
	}

	template<typename T> inline
		std::shared_ptr<T>									alloc_object()
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(CoreApi::GetAllocator());
	}

	template<typename T, typename TP> inline
		std::shared_ptr<T>									alloc_object(TP& p)
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(CoreApi::GetAllocator(), p);
	}

	template<typename T, typename TP1, typename TP2> inline
		std::shared_ptr<T>									alloc_object(TP1& p1, TP2& p2)
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(CoreApi::GetAllocator(), p1, p2);
	}

	inline
		void												log(const std::wstring& text)
	{
		CoreApi::Log(text);
	}

	inline
		void												log(const std::string& text)
	{
		std::wstring log;
		ld3d::Unicode::ANSI_2_UTF16(text, log);
		
		CoreApi::Log(log);
	}


}
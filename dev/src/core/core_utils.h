#pragma once

#include "core/CoreApi.h"

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
		return alloc_object<T>(CoreApi::GetAllocator());
	}

	template<typename T, typename TP> inline
		std::shared_ptr<T>									alloc_object(const TP& p)
	{
		return alloc_object<T>(CoreApi::GetAllocator(), p);
	}



	template<typename T, typename TP1, typename TP2> inline
		std::shared_ptr<T>									alloc_object(const TP1& p1, const TP2& p2)
	{
		return alloc_object<T>(CoreApi::GetAllocator(), p1, p2);
	}

	template<typename T, typename TP1, typename TP2, typename TP3> inline
		std::shared_ptr<T>									alloc_object(const TP1& p1, const TP2& p2, const TP3& p3)
	{
		return alloc_object<T>(CoreApi::GetAllocator(), p1, p2, p3);
	}
	inline
		Logger&												logger()
	{
		return CoreApi::logger();
	}
}

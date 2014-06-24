#pragma once


namespace ld3d
{
	template <typename T> inline
		void											_release_and_reset(std::shared_ptr<T>& pObj)
	{
		if(pObj)
		{
			pObj->Release();
			pObj.reset();
		}
	}

	template <typename T> inline
		void											utils_set_bit(T& bits, unsigned int pos, bool val)
	{
		if(val)
		{
			bits |= (1 << pos);
		}
		else
		{
			bits &= ~(1 << pos);
		}
	}

	template <typename T> inline
		bool											utils_get_bit(T bits, unsigned int pos)
	{
		return (bits & (1 << pos)) != 0;
	}
}


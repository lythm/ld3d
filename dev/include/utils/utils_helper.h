#pragma once

template <typename T> inline
	void											_release_and_reset(std::shared_ptr<T>& pObj)
{
	if(pObj)
	{
		pObj->Release();
		pObj.reset();
	}
}

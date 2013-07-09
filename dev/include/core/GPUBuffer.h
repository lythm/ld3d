#pragma once

namespace ld3d
{
	class GPUBuffer
	{
	public:

		virtual void*											Map(MAP_HINT hint)									= 0;
		virtual void											Unmap()												= 0;
		virtual uint64											GetBytes() const									= 0;
		virtual void											Release()											= 0;

	protected:
		GPUBuffer(void){}

		virtual ~GPUBuffer(void){}
	};
}

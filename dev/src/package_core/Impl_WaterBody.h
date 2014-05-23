#pragma once
#include "packages/core/WaterBody.h"

namespace ld3d
{
	class Impl_WaterBody : public WaterBody
	{
	public:
		Impl_WaterBody(GameObjectManagerPtr pManager);

		virtual ~Impl_WaterBody(void);

		void												SetSize(uint32 size);
		const uint32&										GetSize() const;

	private:
		uint32												m_size;

	};


}
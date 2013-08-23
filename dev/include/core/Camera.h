#pragma once

#include "core/BaseCamera.h"
namespace ld3d
{

	class _DLL_CLASS Camera : public BaseCamera
	{
	public:
		Camera(void);
		virtual ~Camera(void);

		void								SetOrder(const int& order);
		const int&							GetOrder();

		static bool							SortFunction(CameraPtr pC1, CameraPtr pC2);
	private:
		int									m_order;

	};
}

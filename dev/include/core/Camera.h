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

		void								SetViewport(const math::RectI& vp);
		const math::RectI&					GetViewport() const;

		static bool							SortFunction(CameraPtr pC1, CameraPtr pC2);

		const std::vector<PostEffectPtr>	GetEffectList() const;

		void								AddPostEffect(PostEffectPtr pEffect);
		void								Release();
	private:
		int									m_order;

		math::RectI							m_viewPort;

		std::vector<PostEffectPtr>			m_effects;

	};
}

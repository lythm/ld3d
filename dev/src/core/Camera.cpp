#include "core_pch.h"
#include "core/Camera.h"
#include "core/PostEffect.h"


namespace ld3d
{

	Camera::Camera(void)
	{
		m_order = 0;
		for(auto pe : m_effects)
		{
			pe->Release();
		}
		m_effects.clear();
	}


	Camera::~Camera(void)
	{
	}
	void Camera::SetOrder(const int& order)
	{
		m_order = order;
	}
	const int& Camera::GetOrder()
	{
		return m_order;
	}
	bool Camera::SortFunction(CameraPtr pC1, CameraPtr pC2)
	{
		return pC1->GetOrder() <= pC2->GetOrder();
	}
	void Camera::SetViewport(const math::RectI& vp)
	{
		m_viewPort = vp;
	}
	const math::RectI& Camera::GetViewport() const
	{
		return m_viewPort;
	}
	const std::vector<PostEffectPtr> Camera::GetEffectList() const
	{
		return m_effects;
	}
	void Camera::AddPostEffect(PostEffectPtr pEffect)
	{
		m_effects.push_back(pEffect);
	}
}

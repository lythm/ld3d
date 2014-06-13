#include "core_pch.h"
#include "core/Light.h"

namespace ld3d
{

	Light::Light(LIGHT_TYPE type)
	{
		m_type = type;

		m_bCastShadow				= false;
		m_diffClr					= math::Color4(1.0f, 1.0f, 1.0f, 1.0f);

		m_intensity					= 1.0f;
		m_bEnabled					= true;

		m_shadowMapWidth			= 640;
		m_shadowMapHeight			= 640;

		m_worldTM.MakeIdentity();
	}


	Light::~Light(void)
	{
	}
	void Light::Update()
	{
	}
	void Light::RenderShadowMap(RenderManagerPtr pRenderer)
	{
	}
	RenderTexturePtr Light::GetShadowMap()
	{
		return RenderTexturePtr();
	}
	LIGHT_TYPE Light::GetType() const
	{
		return m_type;
	}
	
	bool Light::IsAffecting(const math::ViewFrustum& frustum)
	{
		return true;
	}
	void Light::Release()
	{
	}
	const math::Matrix44& Light::GetWorldTM()
	{
		return m_worldTM;
	}
	void Light::SetWorldTM(const math::Matrix44& world)
	{
		m_worldTM = world;
	}
	const math::Color4& Light::GetDiffuseColor()
	{
		return m_diffClr;
	}
	void Light::SetDiffuseColor(const math::Color4& clr)
	{
		m_diffClr = clr;
	}
	
	const bool& Light::GetCastShadow()
	{
		return m_bCastShadow;
	}
	void Light::SetCastShadow(const bool& bCast)
	{
		m_bCastShadow = bCast;
	}
	const float& Light::GetIntensity()
	{
		return m_intensity;
	}
	void Light::SetIntensity(const float& i)
	{
		m_intensity = i > 1.0f ? 1.0f : i;
	}
	const bool&	Light::GetEnabled()
	{
		return m_bEnabled;
	}
	void Light::SetEnabled(const bool& bEnabled)
	{
		m_bEnabled = bEnabled;
	}
	void Light::RenderLight(RenderManagerPtr pRenderer)
	{

	}
	void Light::SetShadowMapSize(uint32 w, uint32 h)
	{
		m_shadowMapWidth = w;
		m_shadowMapHeight = h;
		ResizeShadowMap();
	}
	void Light::GetShadowMapSize(uint32& w, uint32& h)
	{
		w = m_shadowMapWidth;
		h = m_shadowMapHeight;
	}
	void Light::ResizeShadowMap()
	{
	}
}

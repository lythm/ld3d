#pragma once
#include <boost/enable_shared_from_this.hpp>

#include "core/ViewFrustum.h"

namespace ld3d
{
	class _DLL_CLASS Light: public std::enable_shared_from_this<Light>
	{
		friend class LightManager;

	public:
		
		Light(LIGHT_TYPE type);
		virtual ~Light(void);

		virtual void							RenderLight(RenderManagerPtr pRenderer);
		virtual void							Update();
		virtual void							RenderShadowMap(RenderManagerPtr pRenderer);
		virtual bool							IsAffecting(const ViewFrustum& frustum);
		virtual void							Release();
		virtual const math::Matrix44&			GetWorldTM();
		virtual void							SetWorldTM(const math::Matrix44& world);

		
		virtual RenderTexturePtr				GetShadowMap();

		
		LIGHT_TYPE								GetType() const;

		

		const math::Color4&						GetDiffuseColor();
		void									SetDiffuseColor(const math::Color4& clr);

		const bool&								GetCastShadow();
		void									SetCastShadow(const bool& bCast);

		const float&							GetIntensity();
		void									SetIntensity(const float& i);

		const bool&								GetEnabled();
		void									SetEnabled(const bool& bEnabled);
		
	protected:
		LIGHT_TYPE								m_type;

		LightPtr								m_pPrev;
		LightPtr								m_pNext;

		math::Matrix44							m_worldTM;

		bool									m_bCastShadow;
		math::Color4							m_diffClr;
		float									m_intensity;

		bool									m_bEnabled;
	};
}

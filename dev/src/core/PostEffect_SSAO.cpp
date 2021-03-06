#include "core_pch.h"
#include "core/PostEffect_SSAO.h"
#include "core/RenderManager.h"
#include "core/Material.h"
#include "core/Sys_Graphics.h"
#include "core/Texture.h"
#include "core/RenderTexture.h"
#include "core/materialparameter.h"
#include "core_utils.h"

namespace ld3d
{
	PostEffect_SSAO::PostEffect_SSAO(void)
	{
		m_randomTexSize				= 64;
		m_sampleRad					= 2;
		m_intensity					= 2;
		m_scale						= 3;
		m_bias						= cosf(math::D2R(70));
		m_bBlur						= true;
	}


	PostEffect_SSAO::~PostEffect_SSAO(void)
	{
	}
	bool PostEffect_SSAO::Initialize(RenderManagerPtr pRenderManager)
	{
		
		m_pMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_ssao.fx");

		

		m_pSSAORandomTex = pRenderManager->CreateTextureFromFile("./assets/standard/texture/ssao_rand.jpg");
		
		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("tex_ssao_rand");
		pParam->SetParameterTexture(m_pSSAORandomTex);


		int w = pRenderManager->GetFrameBufferWidth();

		int h = pRenderManager->GetFrameBufferHeight();
		G_FORMAT rt_format[1] = {G_FORMAT_R8G8B8A8_UNORM,};
		m_pGBlurTarget = pRenderManager->CreateRenderTexture(1, w , h , rt_format);

		if(m_pGBlurTarget == nullptr)
		{
			return false;
		}

		m_pGBlurMaterial = pRenderManager->CreateMaterialFromFile("./assets/standard/material/dr_render_BBlur.fx");

		if(m_pGBlurMaterial == nullptr)
		{
			return false;
		}
		
		return true;
	}
	void PostEffect_SSAO::Release()
	{
		_release_and_reset(m_pGBlurTarget);

		_release_and_reset(m_pGBlurMaterial);

		_release_and_reset(m_pSSAORandomTex);

		_release_and_reset(m_pMaterial);

	}

	void PostEffect_SSAO::Render(RenderManagerPtr pRenderer, RenderTexturePtr pInput, RenderTexturePtr pOutput)
	{
		pRenderer->SetRenderTarget(m_pGBlurTarget);
		pRenderer->ClearRenderTarget(0, math::Color4(0, 0, 0,0));

		pRenderer->SetDRBuffer(m_pMaterial);

		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("g_screen_size");
		pParam->SetParameterVector(math::Vector2((Real)pRenderer->GetFrameBufferWidth(), (Real)pRenderer->GetFrameBufferHeight()));

		pParam = m_pMaterial->GetParameterByName("g_scale");
		pParam->SetParameterFloat(m_scale);

		pParam = m_pMaterial->GetParameterByName("g_random_size");
		pParam->SetParameterFloat(m_randomTexSize);

		pParam = m_pMaterial->GetParameterByName("g_sample_rad");
		pParam->SetParameterFloat(m_sampleRad);

		pParam = m_pMaterial->GetParameterByName("g_bias");
		pParam->SetParameterFloat(m_bias);
		
		pParam = m_pMaterial->GetParameterByName("g_intensity");
		pParam->SetParameterFloat(m_intensity);

		pRenderer->DrawFullScreenQuad(m_pMaterial);

		pRenderer->SetRenderTarget(pOutput);
		pRenderer->ClearRenderTarget(0, math::Color4(0, 0, 0,0));
		
		pRenderer->SetGBuffer(m_pGBlurMaterial);
		
		pParam = m_pMaterial->GetParameterByName("tex_ao");
		pParam->SetParameterTexture(m_pGBlurTarget->GetTexture(0));

		 pParam = m_pMaterial->GetParameterByName("g_input_size");
		pParam->SetParameterVector(math::Vector2((Real)pRenderer->GetFrameBufferWidth(), (Real)pRenderer->GetFrameBufferHeight()));
		
		pParam = m_pMaterial->GetParameterByName("tex_input");
		pParam->SetParameterTexture(pInput->GetTexture(0));

		
		pRenderer->DrawFullScreenQuad(m_pGBlurMaterial);
	}
	const float& PostEffect_SSAO::GetBias()
	{
		return m_bias;
	}
	const float& PostEffect_SSAO::GetIntensity()
	{
		return m_intensity;
	}
	const float& PostEffect_SSAO::GetScale()
	{
		return m_scale;
	}
	const float& PostEffect_SSAO::GetSampleRad()
	{
		return m_sampleRad;
	}

	void PostEffect_SSAO::SetBias(const float& bias)
	{
		m_bias = bias;
	}
	void PostEffect_SSAO::SetIntensity(const float& intensity)
	{
		m_intensity = intensity;
	}
	void PostEffect_SSAO::SetScale(const float& scale)
	{
		m_scale = scale;
	}
	void PostEffect_SSAO::SetSampleRad(const float& rad)
	{
		m_sampleRad = rad;
	}
	const bool&	PostEffect_SSAO::GetBlur()
	{
		return m_bBlur;
	}
	void PostEffect_SSAO::SetBlur(const bool& blur)
	{
		m_bBlur = blur;
	}
}


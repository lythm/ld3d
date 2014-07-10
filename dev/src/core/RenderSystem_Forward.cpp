#include "core_pch.h"
#include "RenderSystem_Forward.h"
#include "core/RenderManager.h"
#include "RenderQueue.h"
#include "core/RenderData.h"
#include "core/Material.h"

namespace ld3d
{
	RenderSystem_Forward::RenderSystem_Forward(void)
	{
	}


	RenderSystem_Forward::~RenderSystem_Forward(void)
	{
	}
	bool RenderSystem_Forward::Initialize(RenderManagerPtr pRenderManager)
	{
		m_pRenderManager = pRenderManager;
		return true;
	}
	void RenderSystem_Forward::Release()
	{
		m_pRenderManager.reset();
	}
	void RenderSystem_Forward::Render(RenderQueuePtr pRenderQueue, RenderTargetPtr pTarget)
	{
		m_pRenderManager->SetRenderTarget(pTarget);

		for(uint32 iLayer = layer_forward; iLayer < layer_overlay; ++iLayer)
		{
			for(uint32 i = 0; i < pRenderQueue->GetRenderDataCount(iLayer); ++i)
			{
				RenderDataPtr pData = pRenderQueue->GetRenderData(iLayer, i);
				
				if(pData->fr_draw)
				{
					pData->fr_draw(m_pRenderManager);
					continue;
				}
				m_pRenderManager->SetMatrixBlock(pData->material, pData->world_matrix);
				m_pRenderManager->DrawRenderData(pData);
			}
		}
	}
}

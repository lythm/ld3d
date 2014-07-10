#pragma once

namespace ld3d
{
	class RenderSystem_Forward
	{
	public:
		RenderSystem_Forward(void);
		virtual ~RenderSystem_Forward(void);

		bool												Initialize(RenderManagerPtr pRenderManager);
		void												Release();

		void												Render(RenderQueuePtr pRenderQueue, RenderTargetPtr pTarget);

	private:
		RenderManagerPtr									m_pRenderManager;
	};


}

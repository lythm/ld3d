#pragma once

namespace ld3d
{
	class RenderQueue
	{
	public:
		

		RenderQueue(void);
		virtual ~RenderQueue(void);

		bool											Initialize(uint32 nLayers = 10);
		void											Release();

		uint32											GetLayerCount() const;

		void											ClearAll();
		void											ClearLayer(uint32 index);

		void											AddRenderData(uint32 layer, RenderDataPtr pData);

		uint32											GetRenderDataCount(uint32 layer);

		RenderDataPtr									GetRenderData(uint32 layer, uint32 index);

	private:
		std::vector<std::vector<RenderDataPtr>>			m_layers;
	};
}

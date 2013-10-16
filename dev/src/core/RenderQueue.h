#pragma once

namespace ld3d
{
	class RenderQueue
	{
	public:
		struct Layer
		{
			std::vector<RenderDataPtr>					m_dr;
			std::vector<RenderDataPtr>					m_fr;
		};

		RenderQueue(void);
		virtual ~RenderQueue(void);

		bool											Initialize(uint32 nLayers = 10);
		void											Release();

		uint32											GetLayerCount() const;

		void											ClearAll();
		void											ClearLayer(uint32 index);

		void											AddRenderData(uint32 layer, RenderDataPtr pData);

		uint32											DR_GetRenderDataCount(uint32 layer);
		uint32											FR_GetRenderDataCount(uint32 layer);

		RenderDataPtr									DR_GetRenderData(uint32 layer, uint32 index);
		RenderDataPtr									FR_GetRenderData(uint32 layer, uint32 index);

	private:
		std::vector<Layer>								m_layers;
	};
}

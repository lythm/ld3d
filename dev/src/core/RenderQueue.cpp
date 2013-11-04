#include "core_pch.h"
#include "RenderQueue.h"
#include "core_utils.h"
#include "core/RenderData.h"

namespace ld3d
{
	RenderQueue::RenderQueue(void)
	{
		
	}


	RenderQueue::~RenderQueue(void)
	{
	}
	bool RenderQueue::Initialize(uint32 nLayers)
	{
		if(nLayers == 0)
		{
			return false;
		}
		m_layers.resize(nLayers);
		return true;
	}
	void RenderQueue::Release()
	{
		m_layers.clear();
	}
	uint32 RenderQueue::GetLayerCount() const
	{
		return (uint32)m_layers.size();
	}
	void RenderQueue::ClearAll()
	{
		for(size_t i = 0; i < m_layers.size(); ++i)
		{
			ClearLayer(i);
		}
	}
	void RenderQueue::ClearLayer(uint32 index)
	{
		m_layers[index].clear();
	}
	void RenderQueue::AddRenderData(uint32 layer, RenderDataPtr pData)
	{
		m_layers[layer].push_back(pData);
	}
	uint32 RenderQueue::GetRenderDataCount(uint32 layer)
	{
		return (uint32)m_layers[layer].size();
	}
	
	RenderDataPtr RenderQueue::GetRenderData(uint32 layer, uint32 index)
	{
		return m_layers[layer][index];
	}
	
}

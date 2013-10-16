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
		m_layers[index].m_dr.clear();
		m_layers[index].m_fr.clear();
	}
	void RenderQueue::AddRenderData(uint32 layer, RenderDataPtr pData)
	{
		if(pData->dr)
		{
			m_layers[layer].m_dr.push_back(pData);
		}
		else
		{
			m_layers[layer].m_fr.push_back(pData);
		}
	}
	uint32 RenderQueue::DR_GetRenderDataCount(uint32 layer)
	{
		return (uint32)m_layers[layer].m_dr.size();
	}
	uint32 RenderQueue::FR_GetRenderDataCount(uint32 layer)
	{
		return (uint32)m_layers[layer].m_fr.size();
	}
	RenderDataPtr RenderQueue::DR_GetRenderData(uint32 layer, uint32 index)
	{
		return m_layers[layer].m_dr[index];
	}
	RenderDataPtr RenderQueue::FR_GetRenderData(uint32 layer, uint32 index)
	{
		return m_layers[layer].m_fr[index];
	}
}

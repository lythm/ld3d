#pragma once

#include "packages/voxel/VoxelWorldRenderer.h"

namespace ld3d
{
	struct VoxelWorldChunk;

	class VoxelWorldRendererImpl : public VoxelWorldRenderer
	{
	public:
		VoxelWorldRendererImpl(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldRendererImpl(void);

		void										Update(float dt);

		const bool&									GetShowBound();
		void										SetShowBound(const bool& show);

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version);

	private:
		bool										OnAttach();
		void										OnDetach();

		void										on_event_frustumcull(EventPtr pEvent);

		void										Render(RenderManagerPtr pManager);
		void										Draw(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial, int baseVertex);
	private:

		EventHandlerID								m_hFrustumCull;
		VoxelWorldImplPtr							m_pWorld;

		bool										m_bShowBound;

		BBoxRenderDataPtr							m_pBBoxRD;


		RenderDataPtr								m_pRenderData;

		VoxelWorldChunk*							m_pRenderList;

		MaterialPtr									m_pMaterial;
		
		uint32										m_nVBBytes;
		uint32										m_nVBCurrent;
		uint32										m_nVBOffset;
		uint32										m_nVertexStride;
		uint32										m_nVertexCount;

		GeometryDataPtr								m_pGeometry;

		RenderManagerPtr							m_pRenderManager;

		math::Matrix44								m_worldMatrix;
	};
}

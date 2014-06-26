#pragma once


#include "packages/voxel/VoxelWorldRenderer.h"
namespace ld3d
{
	class VoxelWorldRendererImpl : public VoxelWorldRenderer
	{
		struct RenderUnit
		{
			voxel::Coord							base;
			voxel::ChunkMeshPtr						mesh;
			voxel::ChunkMesh::Subset				sub;
		};
		typedef std::vector<RenderUnit>				RenderList;
	public:
		VoxelWorldRendererImpl(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldRendererImpl(void);


		const bool&									GetShowBound();
		void										SetShowBound(const bool& show);


		void										Update(float dt);

		void										BindWorldViewPort(GameObjectPtr pNode);
		void										MoveViewPortTo(uint32 x, uint32 y, uint32 z);

		void										ResetWorld(voxel::WorldPtr pWorld, const std::vector<MaterialPtr>& mats);
		void										SetWorldViewPort(const voxel::Coord& center, uint32 size);

		void										RefreshMesh();

		uint32										GetRenderedFaceCount();

	private:
		void										on_event_frustumcull(EventPtr pEvent);
		bool										OnAttach();
		void										OnDetach();

		void										_add_mesh(const voxel::Coord& base, voxel::ChunkMeshPtr pMesh);
		void										Draw(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial, int baseVertex);
		void										Render(RenderManagerPtr pManager);
		void										RenderShadowMapGeo(RenderManagerPtr pManager, MaterialPtr pMaterial);

		void										_render(size_t begin, size_t end);
		void										_render_smg(size_t begin, size_t end, MaterialPtr pMaterial);
	private:
		bool										m_bShowBound;

		GameObjectPtr								m_pViewPortRoot;

		voxel::WorldViewportPtr						m_pWorldVP;
		
		EventHandlerID								m_hFrustumCull;

		
		RenderList									m_renderList;
				
		RenderDataPtr								m_pRenderData;

		AABBoxRenderDataPtr							m_pAABBoxRenderData;
		uint32										m_nVBBytes;
		uint32										m_nVBCurrent;
		uint32										m_nVBOffset;
		uint32										m_nVertexStride;
		uint32										m_nVertexCount;

		GeometryDataPtr								m_pGeometry;

		RenderManagerPtr							m_pRenderManager;

		math::Matrix44								m_worldMatrix;
		std::vector<MaterialPtr>					m_materials;

		uint32										m_renderedFaces;
	};
}

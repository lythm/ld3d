#pragma once

namespace ld3d
{
	class VoxelWorldRenderData : public RenderData
	{
		struct VoxelVertex
		{
			math::Vector3				pos;
			math::Vector3				normal;
		};
	public:
		VoxelWorldRenderData(void);
		virtual ~VoxelWorldRenderData(void);

		bool													Initialize(Sys_GraphicsPtr pGraphics);
		void													Release();

		void													Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial = MaterialPtr());
		MaterialPtr												GetMaterial();
		math::Matrix44											GetWorldMatrix();
		bool													IsDeferred();

		void													PrepareData(const std::vector<VoxelFace>& data);

	private:
		GPUBufferPtr											m_pVertexBuffer;
		GPUBufferPtr											m_pIndexBuffer;
		MaterialPtr												m_pMaterial;

		Sys_GraphicsPtr											m_pGraphics;

		uint32													m_nVBBytes;
		uint32													m_nVBCurrent;
		uint32													m_nVBOffset;
		uint32													m_nVertexStride;
		uint32													m_nVertexCount;
	};
}

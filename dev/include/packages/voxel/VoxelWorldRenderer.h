#pragma once

namespace ld3d
{
	class VoxelWorldRenderer : public GameObjectComponent
	{
	public:
		

		virtual const bool&									GetShowBound()								= 0;
		virtual void										SetShowBound(const bool& show)				= 0;

		virtual void										BindWorldViewPort(GameObjectPtr pNode)		= 0;
		virtual void										RefreshMesh(){};
		virtual uint32										GetRenderedFaceCount()						= 0;
		virtual uint32										GetRenderedVertexCount()					= 0;
		virtual uint32										GetRenderedVertexBytes()					= 0;
		virtual uint32										GetRenderedChunkCount()						= 0;
	protected:
		VoxelWorldRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("Voxel.WorldRenderer", pManager){}
		virtual ~VoxelWorldRenderer(void){}
	};
}

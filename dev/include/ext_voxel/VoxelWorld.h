#pragma once

namespace ld3d
{
	struct Voxel;
	class VoxelWorld : public GameObjectComponent
	{
	public:

		VoxelWorld(GameObjectManagerPtr pManager);
		virtual ~VoxelWorld(void);

		void										Update(float dt);
		
		void										AddBlock(Voxel* pVoxel);
		void										RemoveBlock();

		const int&									GetVoxelSize();
		void										SetVoxelSize(const int& size);

		const int&									GetWorldSizeY();
		void										SetWorldSizeY(const int& y);

		const int&									GetWorldSizeX();
		void										SetWorldSizeX(const int& x);

		const int&									GetWorldSizeZ();
		void										SetWorldSizeZ(const int& z);

		void										Generate();
		const Version&								GetVersion() const;

		void										FrustumCull(BaseCameraPtr pCamera);
	private:
		bool										OnAttach();
		void										OnDetach();

		void										RebuildWorld();
		void										DestroyWorld();
		void										Polygonize();

	private:
		int											m_voxelSize;
		int											m_worldSizeX;
		int											m_worldSizeY;
		int											m_worldSizeZ;

		std::vector<Voxel*>							m_voxels;
		VoxelPolygonizerPtr							m_pPolygonizer;

		OctTreeNodePtr								m_pRoot;

		VoxelPoolPtr								m_pVoxelPool;
	};
}

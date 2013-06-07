#pragma once

namespace ld3d
{
	struct VoxelWorldChunk;
	
	class VoxelWorld : public GameObjectComponent
	{
	public:

		VoxelWorld(GameObjectManagerPtr pManager);
		virtual ~VoxelWorld(void);

		void										Update(float dt);
		
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

		VoxelWorldChunk*							FrustumCull(BaseCameraPtr pCamera);

		VoxelWorldDataSetPtr						GetDataSet();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version);
	private:
		bool										OnAttach();
		void										OnDetach();

		void										RebuildWorld();
		void										DestroyWorld();

	private:
		int											m_voxelSize;
		int											m_worldSizeX;
		int											m_worldSizeY;
		int											m_worldSizeZ;

		VoxelWorldDataSetPtr						m_pDataSet;
	};
}

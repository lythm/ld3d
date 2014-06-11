#pragma once

#include "packages/voxel/VoxelWorld.h"
namespace ld3d
{
	class VoxelWorldImpl2 : public VoxelWorld
	{
	public:
		VoxelWorldImpl2(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldImpl2(void);


		const int&									GetVoxelSize();
		void										SetVoxelSize(const int& size);

		const int&									GetWorldSizeY();
		void										SetWorldSizeY(const int& y);

		const int&									GetWorldSizeX();
		void										SetWorldSizeX(const int& x);

		const int&									GetWorldSizeZ();
		void										SetWorldSizeZ(const int& z);


		bool										CreateWorld(const std::string& name);
		void										DestroyWorld();

		void										Update(float dt);

		void										_on_end_frame(EventPtr pEvent);
		voxel::WorldPtr								GetWorld();
	private:

		void										ResetComponents();

		bool										OnAttach();
		void										OnDetach();
	private:
		int											m_voxelSize;
		int											m_worldSizeX;
		int											m_worldSizeY;
		int											m_worldSizeZ;

		voxel::WorldPtr								m_pWorld;

		EventHandlerID								m_hEndFrame;
	};


}
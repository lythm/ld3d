#pragma once

#include "packages/voxel/VoxelWorldCollisionData.h"

namespace ld3d
{
	class VoxelWorldCollisionDataImpl : public VoxelWorldCollisionData
	{
	public:
		VoxelWorldCollisionDataImpl(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldCollisionDataImpl(void);

		void										Update(float dt);

	private:

		bool										OnAttach();
		void										OnDetach();

	private:

		CollisionDataPtr							m_pCD;
		VoxelWorldBoundPtr							m_pBound;

		PhysicsManagerPtr							m_pPhysicsManager;

		VoxelWorldImplPtr							m_pWorld;
	};


}
#pragma once

namespace ld3d
{
	class VoxelWorldTemplate : public GameObjectTemplate
	{
	public:
		VoxelWorldTemplate(GameObjectManagerPtr pManager, const std::string& name);
		virtual ~VoxelWorldTemplate(void);

		GameObjectPtr					CreateGameObject();
		void							Release();

	};
}
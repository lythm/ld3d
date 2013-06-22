#pragma once

namespace dt
{
	class DT_VoxelWorldEditor : public ld3d::GameObjectComponent
	{
	public:
		DT_VoxelWorldEditor(ld3d::GameObjectManagerPtr pManager);
		virtual ~DT_VoxelWorldEditor(void);

		static ld3d::ExtPackage::ComponentClass*						GetClass();

	private:

		static ld3d::ExtPackage::ComponentClass							s_class;

	};


}
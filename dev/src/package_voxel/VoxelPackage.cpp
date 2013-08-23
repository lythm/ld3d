#include "voxel_pch.h"

#include "VoxelPackage.h"

#include "ext_voxel/VoxelWorld.h"
#include "ext_voxel/VoxelWorldRenderer.h"
#include "ext_voxel/VoxelObject.h"
#include "ext_voxel/VoxelObjectRenderer.h"
#include "ext_voxel/VoxelWorldGenerator.h"


#include "VoxelWorldTemplate.h"
#include "VoxelObjectTemplate.h"


_DLL_API ld3d::Package* CreatePackage(ld3d::GameObjectManagerPtr pManager)
{
	return new ld3d::VoxelPackage(pManager);
}


_DLL_API void DestroyPackage(ld3d::Package* pPackage)
{
	delete (ld3d::VoxelPackage*)pPackage;
}

namespace ld3d
{
	VoxelPackage::VoxelPackage(GameObjectManagerPtr pManager)
	{
		
		m_pManager = pManager;

		m_classes.push_back(ComponentClass("VoxelWorld",
							"Voxel",
							"Voxel World",
							&Create_Component<VoxelWorld>));
		m_classes.push_back(ComponentClass("VoxelWorldGenerator",
							"Voxel",
							"Voxel World Generator",
							&Create_Component<VoxelWorldGenerator>));
		m_classes.push_back(ComponentClass("VoxelWorldRenderer",
							"Voxel",
							"Voxel World Renderer",
							&Create_Component<VoxelWorldRenderer>));

		m_classes.push_back(ComponentClass("VoxelObject",
							"Voxel",
							"Voxel Object",
							&Create_Component<VoxelObject>));
		m_classes.push_back(ComponentClass("VoxelObjectRenderer",
							"Voxel",
							"Voxel Object Renderer",
							&Create_Component<VoxelObjectRenderer>));

		// templates
		GameObjectTemplate* pTpl = new VoxelWorldTemplate(m_pManager, "VoxelWorld");
		m_tpls.push_back(pTpl);

		pTpl = new VoxelObjectTemplate(m_pManager, "VoxelObject");
		m_tpls.push_back(pTpl);
	}


	VoxelPackage::~VoxelPackage(void)
	{
	}
	void VoxelPackage::Release()
	{
		m_classes.clear();
		for(size_t i = 0; i < m_tpls.size(); ++i)
		{
			m_tpls[i]->Release();
			delete m_tpls[i];
		}
		m_tpls.clear();
	}
	const char* VoxelPackage::GetPackageName()
	{
		return "Voxel";
	}
	
	int VoxelPackage::GetClassCount()
	{
		return (int)m_classes.size();
	}
	VoxelPackage::ComponentClass* VoxelPackage::GetClassByIndex(int index)
	{
		return &m_classes[index];
	}
	int	VoxelPackage::GetTemplateCount()
	{
		return (int)m_tpls.size();
	}
	GameObjectTemplate* VoxelPackage::GetTemplateByIndex(int index)
	{
		return m_tpls[index];
	}
}


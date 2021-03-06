#include "voxel_pch.h"

#include "VoxelPackage.h"

#include "VoxelWorldImpl.h"
#include "VoxelWorldRendererImpl.h"
#include "VoxelObjectImpl.h"
#include "VoxelObjectRendererImpl.h"

#include "VoxelWorldTemplate.h"
#include "VoxelObjectTemplate.h"



static ld3d::GameObjectManagerPtr				g_pManager;

namespace ld3d
{
	GameObjectManagerPtr GetManager()
	{
		return g_pManager;
	}
}

_DLL_API ld3d::Package* CreatePackage(ld3d::GameObjectManagerPtr pManager)
{
	g_pManager = pManager;
	return new ld3d::VoxelPackage(pManager);
}


_DLL_API void DestroyPackage(ld3d::Package* pPackage)
{
	delete (ld3d::VoxelPackage*)pPackage;
	g_pManager.reset();
}

namespace ld3d
{
	VoxelPackage::VoxelPackage(GameObjectManagerPtr pManager)
	{
		
		m_pManager = pManager;

		m_classes.push_back(ComponentClass("Voxel.World",
							"Voxel",
							"Voxel World",
							&Create_Component<VoxelWorldImpl>));
		m_classes.push_back(ComponentClass("Voxel.WorldRenderer",
							"Voxel",
							"Voxel World Renderer",
							&Create_Component<VoxelWorldRendererImpl>));

		
		m_classes.push_back(ComponentClass("Voxel.Object",
							"Voxel",
							"Voxel Object",
							&Create_Component<VoxelObjectImpl>));
		m_classes.push_back(ComponentClass("Voxel.ObjectRenderer",
							"Voxel",
							"Voxel Object Renderer",
							&Create_Component<VoxelObjectRendererImpl>));

		// templates
		GameObjectTemplate* pTpl = new VoxelWorldTemplate(m_pManager, "Voxel.World");
		m_tpls.push_back(pTpl);

		pTpl = new VoxelObjectTemplate(m_pManager, "Voxel.Object");
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


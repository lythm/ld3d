#include "core_ext_pch.h"
#include "CorePackage.h"


#include "packages/core/WorldMeshRenderer.h"



#include "Impl_SoundEmitter.h"
#include "Impl_SoundListener.h"
#include "Impl_SkyBox.h"
#include "Impl_MeshRenderer.h"
#include "Impl_MeshData.h"
#include "Impl_LuaBehavior.h"
#include "Impl_Light_Spot.h"
#include "Impl_Light_Sky.h"
#include "Impl_Light_Point.h"
#include "Impl_Light_Dir.h"
#include "Impl_CameraData.h"
#include "Impl_CameraController_Orbit.h"
#include "Impl_CameraController_Free.h"
#include "Impl_CollisionData_AABBox.h"
#include "Impl_GridRenderer.h"
#include "Impl_AABBoxRenderer.h"



#include "Tpl_Cube.h"
#include "Tpl_Plane.h"
#include "Tpl_Sphere.h"
#include "Tpl_Cone.h"
#include "Tpl_PointLight.h"
#include "Tpl_SkyLight.h"
#include "Tpl_SpotLight.h"
#include "Tpl_DirLight.h"
#include "Tpl_Camera.h"

_DLL_API ld3d::Package* CreatePackage(ld3d::GameObjectManagerPtr pManager)
{
	return new ld3d::CorePackage(pManager);
}


_DLL_API void DestroyPackage(ld3d::Package* pPackage)
{
	delete (ld3d::CorePackage*)pPackage;
}



namespace ld3d
{
	CorePackage::CorePackage(GameObjectManagerPtr pManager)
	{
		m_pManager = pManager;

		RegisterClasses();

		RegisterTemplates();
	}
	CorePackage::~CorePackage(void)
	{
		m_pManager.reset();
	}
	void CorePackage::RegisterTemplates()
	{
		
		GameObjectTemplate* pTpl = new Tpl_Cube(m_pManager, "Cube");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Plane(m_pManager, "Plane");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Sphere(m_pManager, "Sphere");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Cone(m_pManager, "Cone");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_PointLight(m_pManager, "PointLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_SpotLight(m_pManager, "SpotLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_DirLight(m_pManager, "DirectionalLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_SkyLight(m_pManager, "SkyLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Camera(m_pManager, "Camera");
		m_tpls.push_back(pTpl);

	}
	void CorePackage::RegisterClasses()
	{
		m_classes.push_back(ComponentClass("MeshData",
					"Mesh",
					"Mesh Data",
					&Create_Component<Impl_MeshData>));

		m_classes.push_back(ComponentClass("MeshRenderer",
					"Mesh",
					"Mesh Renderer",
					&Create_Component<Impl_MeshRenderer>));

		m_classes.push_back(ComponentClass("GridRenderer",
					"Mesh",
					"Grid Renderer",
					&Create_Component<Impl_GridRenderer>));

		m_classes.push_back(ComponentClass("AABBoxRenderer",
					"Mesh",
					"AABBox Renderer",
					&Create_Component<Impl_AABBoxRenderer>));

		
		/*m_classes.push_back(ComponentClass("WorldMeshRenderer",
					"Mesh",
					"World Mesh Renderer",
					&Package::Create_WorldMeshRenderer));
					*/

		m_classes.push_back(ComponentClass("DirectionalLight",
					"Light",
					"Directional Light",
					&Create_Component<Impl_Light_Dir>));

		m_classes.push_back(ComponentClass("PointLight",
					"Light",
					"Point Light",
					&Create_Component<Impl_Light_Point>));

		m_classes.push_back(ComponentClass("SpotLight",
					"Light",
					"Spot Light",
					&Create_Component<Impl_Light_Spot>));

		m_classes.push_back(ComponentClass("SkyLight",
					"Light",
					"Sky Light",
					&Create_Component<Impl_Light_Sky>));

		m_classes.push_back(ComponentClass("SkyBox",
					"Sky",
					"SkyBox",
					&Create_Component<Impl_SkyBox>));

		m_classes.push_back(ComponentClass("Camera",
					"Camera",
					"Camera",
					&Create_Component<Impl_CameraData>));

		m_classes.push_back(ComponentClass("CameraOrbitController",
					"Camera",
					"Camera",
					&Create_Component<Impl_CameraController_Orbit>));

		m_classes.push_back(ComponentClass("CameraFreeController",
					"Camera",
					"Camera",
					&Create_Component<Impl_CameraController_Free>));

		

		m_classes.push_back(ComponentClass("LuaBehavior",
					"Script",
					"Lua script Behavior",
					&Create_Component<Impl_LuaBehavior>));

		m_classes.push_back(ComponentClass("SoundEmitter",
					"Sound",
					"Sound Emitter",
					&Create_Component<Impl_SoundEmitter>));

		m_classes.push_back(ComponentClass("SoundListener",
					"Sound",
					"Sound Listener",
					&Create_Component<Impl_SoundListener>));


		m_classes.push_back(ComponentClass("CollisionData_AABBox",
					"Physics",
					"Collision Data for AABBox bound.",
					&Create_Component<Impl_CollisionData_AABBox>));

	}

	
	void CorePackage::Release()
	{
		m_classes.clear();

		for(size_t i = 0; i < m_tpls.size(); ++i)
		{
			m_tpls[i]->Release();
			delete m_tpls[i];
		}
		m_tpls.clear();
	}
	const char* CorePackage::GetPackageName()
	{
		return "Core";
	}
	
	int CorePackage::GetClassCount()
	{
		return (int)m_classes.size();
	}
	CorePackage::ComponentClass* CorePackage::GetClassByIndex(int index)
	{
		return &m_classes[index];
	}

	int	CorePackage::GetTemplateCount()
	{
		return (int)m_tpls.size();
	}
	GameObjectTemplate* CorePackage::GetTemplateByIndex(int index)
	{
		return m_tpls[index];
	}

	
}


#include "core_ext_pch.h"
#include "CorePackage.h"
#include "core/ext/MeshData.h"
#include "core/ext/MeshRenderer.h"
#include "core/ext/WorldMeshRenderer.h"
#include "core/ext/Light_Dir.h"
#include "core/ext/Light_Point.h"
#include "core/ext/Light_Spot.h"
#include "core/ext/Light_Sky.h"
#include "core/ext/SkyBox.h"
#include "core/ext/CameraData.h"
#include "core/ext/Sky.h"
#include "core/ext/PostEffectList.h"
#include "core/ext/LuaBehavior.h"
#include "core/ext/SoundEmitter.h"
#include "core/ext/SoundListener.h"



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
					&Create_Component<MeshData>));

		m_classes.push_back(ComponentClass("MeshRenderer",
					"Mesh",
					"Mesh Renderer",
					&Create_Component<MeshRenderer>));

		
		/*m_classes.push_back(ComponentClass("WorldMeshRenderer",
					"Mesh",
					"World Mesh Renderer",
					&Package::Create_WorldMeshRenderer));
					*/

		m_classes.push_back(ComponentClass("DirectionalLight",
					"Light",
					"Directional Light",
					&Create_Component<Light_Dir>));

		m_classes.push_back(ComponentClass("PointLight",
					"Light",
					"Point Light",
					&Create_Component<Light_Point>));

		m_classes.push_back(ComponentClass("SpotLight",
					"Light",
					"Spot Light",
					&Create_Component<Light_Spot>));

		m_classes.push_back(ComponentClass("SkyLight",
					"Light",
					"Sky Light",
					&Create_Component<Light_Sky>));

		m_classes.push_back(ComponentClass("SkyBox",
					"Sky",
					"SkyBox",
					&Create_Component<SkyBox>));

		m_classes.push_back(ComponentClass("Camera",
					"Camera",
					"Camera",
					&Create_Component<CameraData>));

		m_classes.push_back(ComponentClass("Sky",
					"Rendering",
					"Sky",
					&Create_Component<Sky>));

		m_classes.push_back(ComponentClass("PostEffectList",
					"Camera",
					"PostEffectList",
					&Create_Component<PostEffectList>));

		m_classes.push_back(ComponentClass("LuaBehavior",
					"Script",
					"Lua script Behavior",
					&Create_Component<LuaBehavior>));

		m_classes.push_back(ComponentClass("SoundEmitter",
					"Sound",
					"Sound Emitter",
					&Create_Component<SoundEmitter>));

		m_classes.push_back(ComponentClass("SoundListener",
					"Sound",
					"Sound Listener",
					&Create_Component<SoundListener>));

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


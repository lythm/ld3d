#include "core_ext_pch.h"
#include "CorePackage.h"
#include "core\ext\MeshData.h"
#include "core\ext\MeshRenderer.h"
#include "core\ext\PropertyManager.h"
#include "core\ext\WorldMeshRenderer.h"
#include "core\ext\Light_Dir.h"
#include "core\ext\Light_Point.h"
#include "core\ext\Light_Spot.h"
#include "core\ext\Light_Sky.h"
#include "core\ext\SkyBox.h"
#include "core\ext\CameraData.h"
#include "core\ext\Sky.h"
#include "core\ext\PostEffectList.h"
#include "core\ext\LuaBehavior.h"
#include "core\ext\SoundEmitter.h"
#include "core\ext\SoundListener.h"



#include "Tpl_Cube.h"
#include "Tpl_Plane.h"
#include "Tpl_Sphere.h"
#include "Tpl_Cone.h"
#include "Tpl_PointLight.h"
#include "Tpl_SkyLight.h"
#include "Tpl_SpotLight.h"
#include "Tpl_DirLight.h"
#include "Tpl_Camera.h"

EXPORT_C_API ld3d::Package* CreatePackage(ld3d::GameObjectManagerPtr pManager)
{
	return new ld3d::CorePackage(pManager);
}


EXPORT_C_API void DestroyPackage(ld3d::Package* pPackage)
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
		GameObjectTemplate* pTpl = new Tpl_Cube(m_pManager, L"Cube");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Plane(m_pManager, L"Plane");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Sphere(m_pManager, L"Sphere");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Cone(m_pManager, L"Cone");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_PointLight(m_pManager, L"PointLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_SpotLight(m_pManager, L"SpotLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_DirLight(m_pManager, L"DirectionalLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_SkyLight(m_pManager, L"SkyLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Camera(m_pManager, L"Camera");
		m_tpls.push_back(pTpl);

	}
	void CorePackage::RegisterClasses()
	{
		m_classes.push_back(ComponentClass(L"MeshData",
					L"Mesh",
					L"Mesh Data",
					&Create_Component<MeshData>));

		m_classes.push_back(ComponentClass(L"MeshRenderer",
					L"Mesh",
					L"Mesh Renderer",
					&Create_Component<MeshRenderer>));

		m_classes.push_back(ComponentClass(L"PropertyManager",
					L"Misc",
					L"Property Manager",
					&Create_Component<PropertyManager>));

		/*m_classes.push_back(ComponentClass(L"WorldMeshRenderer",
					L"Mesh",
					L"World Mesh Renderer",
					&Package::Create_WorldMeshRenderer));
					*/

		m_classes.push_back(ComponentClass(L"DirectionalLight",
					L"Light",
					L"Directional Light",
					&Create_Component<Light_Dir>));

		m_classes.push_back(ComponentClass(L"PointLight",
					L"Light",
					L"Point Light",
					&Create_Component<Light_Point>));

		m_classes.push_back(ComponentClass(L"SpotLight",
					L"Light",
					L"Spot Light",
					&Create_Component<Light_Spot>));

		m_classes.push_back(ComponentClass(L"SkyLight",
					L"Light",
					L"Sky Light",
					&Create_Component<Light_Sky>));

		m_classes.push_back(ComponentClass(L"SkyBox",
					L"Sky",
					L"SkyBox",
					&Create_Component<SkyBox>));

		m_classes.push_back(ComponentClass(L"Camera",
					L"Camera",
					L"Camera",
					&Create_Component<CameraData>));

		m_classes.push_back(ComponentClass(L"Sky",
					L"Rendering",
					L"Sky",
					&Create_Component<Sky>));

		m_classes.push_back(ComponentClass(L"PostEffectList",
					L"Camera",
					L"PostEffectList",
					&Create_Component<PostEffectList>));

		m_classes.push_back(ComponentClass(L"LuaBehavior",
					L"Script",
					L"Lua script Behavior",
					&Create_Component<LuaBehavior>));

		m_classes.push_back(ComponentClass(L"SoundEmitter",
					L"Sound",
					L"Sound Emitter",
					&Create_Component<SoundEmitter>));

		m_classes.push_back(ComponentClass(L"SoundListener",
					L"Sound",
					L"Sound Listener",
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
	const wchar_t* CorePackage::GetPackageName()
	{
		return L"Core";
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


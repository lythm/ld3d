#pragma once

#include <memory>

#include "core\ext\core_ext_ptr.h"

namespace ld3d
{
	enum RUN_MODE
	{
		RM_RT,			// run time
		RM_DT,			// design time
	};

	class GameObject;
	class GameObjectManager;
	class GameObjectComponent;
	class Scene;

	typedef std::shared_ptr<Scene>											ScenePtr;
	typedef std::shared_ptr<GameObjectManager>								GameObjectManagerPtr;
	typedef std::shared_ptr<GameObject>										GameObjectPtr;
	typedef std::shared_ptr<GameObjectComponent>							GameObjectComponentPtr;


	

	class Sys_Input;
	class Sys_Graphics;
	class Sys_Graphics2;
	class Sys_Sound;
	class Sys_Physics;
	class Sys_Time;
	class Sys_Network;
	class SysManager;

	
	typedef std::shared_ptr<SysManager>						SysManagerPtr;
	typedef std::shared_ptr<Sys_Time>						Sys_TimePtr;
	typedef std::shared_ptr<Sys_Network>					Sys_NetworkPtr;
	typedef std::shared_ptr<Sys_Physics>					Sys_PhysicsPtr;
	typedef std::shared_ptr<Sys_Input>						Sys_InputPtr;
	typedef std::shared_ptr<Sys_Sound>						Sys_SoundPtr;

	typedef std::shared_ptr<Sys_Graphics>					Sys_GraphicsPtr;
	typedef std::shared_ptr<Sys_Graphics2>					Sys_Graphics2Ptr;

	class LightManager;
	class Light;
	class PointLight;
	class DirectionalLight;
	class SpotLight;
	class SkyLight;

	typedef std::shared_ptr<LightManager>					LightManagerPtr;
	typedef std::shared_ptr<Light>						LightPtr;
	typedef std::shared_ptr<PointLight>					PointLightPtr;
	typedef std::shared_ptr<DirectionalLight>				DirectionalLightPtr;
	typedef std::shared_ptr<SpotLight>					SpotLightPtr;
	typedef std::shared_ptr<SkyLight>						SkyLightPtr;
	
	class DataStream;
	class Mesh;
	class SubMesh;
	


	typedef std::shared_ptr<SubMesh>						SubMeshPtr;
	typedef std::shared_ptr<DataStream>					DataStreamPtr;
	typedef std::shared_ptr<Mesh>							MeshPtr;


	class BBoxRenderData;
	class DepthStencilBuffer;
	class RenderData;
	class RenderTarget;
	class RenderTarget2;
	class Texture;
	class Texture2;
	class GPUBuffer;
	class Camera;
	class RenderState;
	class Shader;
	class BaseCamera;
	
	class RenderWindow;
	class RenderWindow2;
	class Material;
	class MaterialPass;
	class MaterialTech;
	class MaterialParameterManager;
	class MaterialParameter;
	class RenderTexture2;
	class GeometryData;
	class ShaderProgram;

	
	typedef std::shared_ptr<BBoxRenderData>					BBoxRenderDataPtr;
	
	typedef std::shared_ptr<Material>						MaterialPtr;
	typedef std::shared_ptr<MaterialPass>					MaterialPassPtr;
	typedef std::shared_ptr<MaterialTech>					MaterialTechPtr;
	typedef std::shared_ptr<MaterialParameterManager>		MaterialParameterManagerPtr;
	typedef std::shared_ptr<MaterialParameter>				MaterialParameterPtr;

	
	typedef std::shared_ptr<ShaderProgram>					ShaderProgramPtr;
	typedef std::shared_ptr<GeometryData>					GeometryDataPtr;
	typedef std::shared_ptr<RenderTexture2>					RenderTexture2Ptr;
	typedef std::shared_ptr<RenderWindow2>					RenderWindow2Ptr;

	typedef std::shared_ptr<RenderWindow>					RenderWindowPtr;
	typedef std::shared_ptr<RenderState>					RenderStatePtr;
	typedef std::shared_ptr<Shader>							ShaderPtr;
	typedef std::shared_ptr<Camera>							CameraPtr;
	typedef std::shared_ptr<BaseCamera>						BaseCameraPtr;
	typedef std::shared_ptr<DepthStencilBuffer>				DepthStencilBufferPtr;
	typedef std::shared_ptr<RenderTarget>					RenderTargetPtr;
	typedef std::shared_ptr<RenderTarget2>					RenderTarget2Ptr;
	typedef std::shared_ptr<RenderData>						RenderDataPtr;
	typedef std::shared_ptr<GPUBuffer>						GPUBufferPtr;
	typedef std::shared_ptr<Texture>						TexturePtr;
	typedef std::shared_ptr<Texture2>						Texture2Ptr;
	

	class CoreApi;
	class RenderManager;
	class PostEffectManager;
	class PostEffect;
	class PostEffect_SSAO;
	class PostEffect_GaussianBlur;

	typedef std::shared_ptr<PostEffect_GaussianBlur>		PostEffect_GaussianBlurPtr;
	typedef std::shared_ptr<PostEffect_SSAO>				PostEffect_SSAOPtr;
	typedef std::shared_ptr<PostEffect>					PostEffectPtr;
	typedef std::shared_ptr<PostEffectManager>			PostEffectManagerPtr;
	typedef std::shared_ptr<RenderManager>				RenderManagerPtr;
	typedef std::shared_ptr<CoreApi>						CoreApiPtr;


	class EventDispatcher;
	class Event;

	typedef std::shared_ptr<Event>						EventPtr;
	typedef std::shared_ptr<EventDispatcher>				EventDispatcherPtr;


	class Sound;
	class SoundChannel;
	typedef std::shared_ptr<Sound>						SoundPtr;
	typedef std::shared_ptr<SoundChannel>					SoundChannelPtr;

	template <typename T> class Asset_T;
	typedef Asset_T<Texture>								TextureAsset;
	typedef Asset_T<Sound>									SoundAsset;
	class Asset;
	class AssetManager;
	
	typedef std::shared_ptr<SoundAsset>					SoundAssetPtr;
	typedef std::shared_ptr<TextureAsset>					TextureAssetPtr;
	typedef std::shared_ptr<Asset>						AssetPtr;
	typedef std::shared_ptr<AssetManager>					AssetManagerPtr;


	class TimerManager;
	typedef std::shared_ptr<TimerManager>					TimerManagerPtr;
	typedef void*											timer_handle;


	class PropertySet;
	class Property;

	typedef std::shared_ptr<PropertySet>					PropertySetPtr;
	typedef std::shared_ptr<Property>						PropertyPtr;

	


	class DT_CoreApi;
	typedef std::shared_ptr<DT_CoreApi>					DT_CoreApiPtr;

}

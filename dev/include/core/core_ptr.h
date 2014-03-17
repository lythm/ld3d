#pragma once

#include <memory>
#include <boost/signals2.hpp>
#include <boost/function.hpp>

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

	class LightManager;
	class Light;
	class PointLight;
	class DirectionalLight;
	class SpotLight;
	class SkyLight;

	typedef std::shared_ptr<LightManager>					LightManagerPtr;
	typedef std::shared_ptr<Light>							LightPtr;
	typedef std::shared_ptr<PointLight>						PointLightPtr;
	typedef std::shared_ptr<DirectionalLight>				DirectionalLightPtr;
	typedef std::shared_ptr<SpotLight>						SpotLightPtr;
	typedef std::shared_ptr<SkyLight>						SkyLightPtr;
	
	class DataStream;
	class Mesh;
	class SubMesh;
	


	typedef std::shared_ptr<SubMesh>						SubMeshPtr;
	typedef std::shared_ptr<DataStream>						DataStreamPtr;
	typedef std::shared_ptr<Mesh>							MeshPtr;


	class BBoxRenderData;
	class DepthStencilBuffer;
	class RenderTarget;
	class Texture;
	class GPUBuffer;
	class Camera;
	class RenderState;
	class Shader;
	class BaseCamera;
	
	class RenderWindow;
	class Material;
	class MaterialPass;
	class MaterialTech;
	class MaterialParameterManager;
	class MaterialParameter;
	
	class RenderData;
	class RenderTexture;
	class GeometryData;
	class ShaderProgram;
	class SamplerState;
	
	typedef std::shared_ptr<BBoxRenderData>					BBoxRenderDataPtr;
	

	typedef std::shared_ptr<Material>						MaterialPtr;
	typedef std::shared_ptr<MaterialPass>					MaterialPassPtr;
	typedef std::shared_ptr<MaterialTech>					MaterialTechPtr;
	typedef std::shared_ptr<MaterialParameterManager>		MaterialParameterManagerPtr;
	typedef std::shared_ptr<MaterialParameter>				MaterialParameterPtr;

	
	typedef std::shared_ptr<ShaderProgram>					ShaderProgramPtr;
	typedef std::shared_ptr<GeometryData>					GeometryDataPtr;
	typedef std::shared_ptr<RenderTexture>					RenderTexturePtr;
	typedef std::shared_ptr<RenderWindow>					RenderWindowPtr;

	typedef std::shared_ptr<RenderState>					RenderStatePtr;
	typedef std::shared_ptr<Shader>							ShaderPtr;
	typedef std::shared_ptr<Camera>							CameraPtr;
	typedef std::shared_ptr<BaseCamera>						BaseCameraPtr;
	typedef std::shared_ptr<DepthStencilBuffer>				DepthStencilBufferPtr;
	typedef std::shared_ptr<RenderTarget>					RenderTargetPtr;
	typedef std::shared_ptr<RenderData>						RenderDataPtr;
	typedef std::shared_ptr<GPUBuffer>						GPUBufferPtr;
	typedef std::shared_ptr<Texture>						TexturePtr;
	typedef std::shared_ptr<SamplerState>					SamplerStatePtr;
	
	class Bound;
	class PhysicsManager;
	class CollisionData;
	class Bound_AABB;
	class Bound_Sphere;
	class Bound_Complex;

	typedef std::shared_ptr<Bound>							BoundPtr;
	typedef std::shared_ptr<Bound_AABB>						Bound_AABBPtr;
	typedef std::shared_ptr<Bound_Sphere>					Bound_SpherePtr;
	typedef std::shared_ptr<Bound_Complex>					Bound_ComplexPtr;

	typedef std::shared_ptr<CollisionData>					CollisionDataPtr;
	typedef std::shared_ptr<PhysicsManager>					PhysicsManagerPtr;
	


	class CoreApi;
	class RenderManager;
	class PostEffectManager;
	class PostEffect;
	class PostEffect_SSAO;
	class PostEffect_GaussianBlur;

	typedef std::shared_ptr<PostEffect_GaussianBlur>		PostEffect_GaussianBlurPtr;
	typedef std::shared_ptr<PostEffect_SSAO>				PostEffect_SSAOPtr;
	typedef std::shared_ptr<PostEffect>						PostEffectPtr;
	typedef std::shared_ptr<PostEffectManager>				PostEffectManagerPtr;
	typedef std::shared_ptr<RenderManager>					RenderManagerPtr;
	typedef std::shared_ptr<CoreApi>						CoreApiPtr;


	class EventDispatcher;
	class Event;

	typedef std::shared_ptr<Event>							EventPtr;
	typedef std::shared_ptr<EventDispatcher>				EventDispatcherPtr;


	class Sound;
	class SoundChannel;
	typedef std::shared_ptr<Sound>							SoundPtr;
	typedef std::shared_ptr<SoundChannel>					SoundChannelPtr;

	template <typename T> class Asset_T;
	typedef Asset_T<Texture>								TextureAsset;
	typedef Asset_T<Sound>									SoundAsset;
	class Asset;
	class AssetManager;
	
	typedef std::shared_ptr<SoundAsset>						SoundAssetPtr;
	typedef std::shared_ptr<TextureAsset>					TextureAssetPtr;
	typedef std::shared_ptr<Asset>							AssetPtr;
	typedef std::shared_ptr<AssetManager>					AssetManagerPtr;


	class TimerManager;
	typedef std::shared_ptr<TimerManager>					TimerManagerPtr;
	typedef void*											timer_handle;


	class PropertySet;
	class Property;

	typedef std::shared_ptr<PropertySet>					PropertySetPtr;
	typedef std::shared_ptr<Property>						PropertyPtr;

	

	typedef boost::function<void (EventPtr)>				EventHandler;
	typedef boost::signals2::connection						EventHandlerID;


	class DT_CoreApi;
	typedef std::shared_ptr<DT_CoreApi>						DT_CoreApiPtr;


	class WebpageRenderer;
	typedef std::shared_ptr<WebpageRenderer>				WebpageRendererPtr;
	namespace cef
	{
		class CEFManager;
		class CEFWebpageRenderer;

		typedef std::shared_ptr<CEFWebpageRenderer>			CEFWebpageRendererPtr;
		typedef std::shared_ptr<CEFManager>					CEFManagerPtr;
	}

	class UIManager;
	class Overlay;
	class TextureOverlay;
	class HtmlOverlay;

	typedef std::shared_ptr<HtmlOverlay>					HtmlOverlayPtr;
	typedef std::shared_ptr<TextureOverlay>					TextureOverlayPtr;
	typedef std::shared_ptr<Overlay>						OverlayPtr;
	typedef std::shared_ptr<UIManager>						UIManagerPtr;

	namespace material_script
	{
		class SamplerStateParser;
		class RenderStateParser;
		class TechniqueParser;
		class PassParser;
		class BaseParser;

		typedef std::shared_ptr<SamplerStateParser>			SamplerStateParserPtr;
		typedef std::shared_ptr<RenderStateParser>			RenderStateParserPtr;
		typedef std::shared_ptr<TechniqueParser>			TechniqueParserPtr;
		typedef std::shared_ptr<PassParser>					PassParserPtr;
		typedef std::shared_ptr<BaseParser>					BaseParserPtr;

	}


	class ActionManager;
	class GameManager;
	typedef std::shared_ptr<GameManager>					GameManagerPtr;
	typedef std::shared_ptr<ActionManager>					ActionManagerPtr;
}

#pragma once
#if defined(WIN32) || defined(WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "types/dllexport.h"
#include "types/types.h"
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>

#include <boost/signal.hpp>

#include <boost/filesystem.hpp>
#include "core/core_ptr.h"

#include "math/math_all.h"

#include "utils/utils_all.h"

#include "core/Serializer.h"

#include "core/DataStream_File.h"



#include "core/PoolAllocator.h"

#include "core/property_types.h"
#include "core/GameObject.h"
#include "core/GameObjectComponent.h"
#include "core/GameObjectManager.h"
#include "core/GameObjectTemplate.h"

#include "core/ArcBall.h"

#include "core/SysManager.h"
#include "core/Sys_Input.h"
#include "core/Sys_Graphics.h"
#include "core/Sys_Sound.h"
#include "core/Sys_Time.h"

#include "core/Sound.h"
#include "core/SoundChannel.h"

#include "core/BaseCamera.h"
#include "core/Texture.h"

#include "core/Material.h"
#include "core/MaterialCompiler.h"
#include "core/MaterialParameter.h"

#include "core/GPUBuffer.h"
#include "core/VertexFormat.h"
#include "core/RenderTarget.h"
#include "core/RenderWindow.h"
#include "core/RenderTexture.h"
#include "core/DepthStencilBuffer.h"
#include "core/RenderData.h"
#include "core/RenderManager.h"
#include "core/coreapi.h"

#include "core/BBoxRenderData.h"
#include "core/Shader.h"
#include "core/ShaderProgram.h"
#include "core/SamplerState.h"
#include "core/RenderState.h"

#include "core/GeometryData.h"

#include "core/Mesh.h"
#include "core/SubMesh.h"
#include "core/Event.h"
#include "core/MeshUtil.h"
#include "core/Scene.h"

#include "core/Light.h"

#include "core/PostEffect_SSAO.h"
#include "core/PostEffect_BilateralBlur.h"
#include "core/PostEffect_GaussianBlur.h"

#include "core/Camera.h"

#include "core/AssetsManager.h"
#include "core/TimerManager.h"
#include "core/EventDispatcher.h"

#include "core/ext/core_ext_all.h"

#include "core/DT_CoreApi.h"

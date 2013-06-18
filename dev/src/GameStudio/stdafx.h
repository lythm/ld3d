#pragma once

#include <string>

#include "types\dllexport.h"
#include "types\types.h"

#include "utils\utils_all.h"

#include "core\core_all.h"
#include "ext_voxel\voxel_all.h"


#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <QtWidgets>





class Project;
class Renderer;
class GridMesh;
class EditorCamera;
class GameScene;


typedef std::shared_ptr<GameScene>					GameScenePtr;
typedef std::shared_ptr<EditorCamera>				EditorCameraPtr;
typedef std::shared_ptr<GridMesh>					GridMeshPtr;
typedef std::shared_ptr<Renderer>					RendererPtr;
typedef std::shared_ptr<Project>					ProjectPtr;



extern ld3d::PoolAllocator							g_Allocator;

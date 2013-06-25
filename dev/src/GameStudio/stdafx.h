#pragma once

#include <string>
#include <iostream>

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
class GridMesh;
class OrbitCamera;
class GameScene;
class GameEngine;
class GameEditor;
class MenuManager;

typedef std::shared_ptr<MenuManager>				MenuManagerPtr;

typedef std::shared_ptr<GameEditor>					GameEditorPtr;
typedef std::shared_ptr<GameEngine>					GameEnginePtr;
typedef std::shared_ptr<GameScene>					GameScenePtr;
typedef std::shared_ptr<OrbitCamera>				OrbitCameraPtr;
typedef std::shared_ptr<GridMesh>					GridMeshPtr;
typedef std::shared_ptr<Project>					ProjectPtr;



extern ld3d::PoolAllocator							g_Allocator;
extern bool											g_app_running;

template<typename T>
inline std::shared_ptr<T> alloc_shared()
{
	return std::allocate_shared<T, ld3d::std_allocator_adapter<T>>(ld3d::std_allocator_adapter<T>(&g_Allocator));
}

template<typename T, typename arg_T>
inline std::shared_ptr<T> alloc_shared(arg_T&& arg)
{
	return std::allocate_shared<T, ld3d::std_allocator_adapter<T>, arg_T>(ld3d::std_allocator_adapter<T>(&g_Allocator), arg);
}
template<typename T, typename arg0_T, typename arg1_T>
inline std::shared_ptr<T> alloc_shared(arg0_T&& arg0, arg1_T&& arg1)
{
	return std::allocate_shared<T, ld3d::std_allocator_adapter<T>>(ld3d::std_allocator_adapter<T>(&g_Allocator), arg0, arg1);
}


// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS






#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <string>
#include <iostream>

#include "types\dllexport.h"
#include "types\types.h"

#include "utils\utils_all.h"

#include "core\core_all.h"
//#include "ext_voxel\voxel_all.h"
#include <afxcview.h>




class Project;
class Renderer;
class GridMesh;
class EditorCamera;
class AppConfig;
class PathManager;
class GameScene;


typedef std::shared_ptr<GameScene>					GameScenePtr;
typedef std::shared_ptr<PathManager>				PathManagerPtr;
typedef std::shared_ptr<AppConfig>					AppConfigPtr;
typedef std::shared_ptr<EditorCamera>				EditorCameraPtr;
typedef std::shared_ptr<GridMesh>					GridMeshPtr;
typedef std::shared_ptr<Renderer>					RendererPtr;
typedef std::shared_ptr<Project>					ProjectPtr;



extern ld3d::PoolAllocator							g_Allocator;


#define INSPECTOR_PROPERTY_ROW_HEIGHT			20
#define INSPECTOR_PROPERTY_ROW_H_PADDING		10
#define INSPECTOR_PROPERTY_ROW_V_PADDING		6
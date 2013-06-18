
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS






#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









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
#include "ext_voxel\voxel_all.h"
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
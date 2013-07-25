#pragma once


//#define _D3DX9_IMPL_
#define _XNAMATH_IMPL_
//#define _GLM_IMPL_




#ifdef _D3DX9_IMPL_
#pragma comment(lib, "d3dx9.lib")
#endif

#ifdef _GLM_IMPL_
#define GLM_MESSAGES
#define GLM_FORCE_RADIANS
#endif
#pragma once

#include "glext/glcorearb.h"


extern PFNGLGETSTRINGIPROC								glGetStringi;



extern PFNGLCLEARBUFFERFVPROC							glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC							glClearBufferfi;


// debug
extern PFNGLDEBUGMESSAGECONTROLPROC						glDebugMessageControl;
extern PFNGLDEBUGMESSAGEINSERTPROC						glDebugMessageInsert;
extern PFNGLDEBUGMESSAGECALLBACKPROC					glDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC						glGetDebugMessageLog;


// VBO
extern PFNGLGENBUFFERSPROC								glGenBuffers;
extern PFNGLBINDBUFFERPROC								glBindBuffer;
extern PFNGLBUFFERDATAPROC								glBufferData;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC					glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC				glDisableVertexAttribArray;
extern PFNGLISBUFFERPROC								glIsBuffer;	
extern PFNGLBUFFERSUBDATAPROC							glBufferSubData;	
extern PFNGLDELETEBUFFERSPROC							glDeleteBuffers;	
extern PFNGLVERTEXATTRIBPOINTERPROC						glVertexAttribPointer;	
extern PFNGLMAPBUFFERRANGEPROC							glMapBufferRange;	
extern PFNGLUNMAPBUFFERPROC								glUnmapBuffer;	








#include "glext/wglext.h"

// wgl
extern PFNWGLSWAPINTERVALEXTPROC						wglSwapIntervalEXT;

#pragma once
#include <gl/GL.h>
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
extern PFNGLBINDVERTEXBUFFERPROC						glBindVertexBuffer;


// VAO
extern PFNGLGENVERTEXARRAYSPROC							glGenVertexArrays;	
extern PFNGLBINDVERTEXARRAYPROC							glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC						glDeleteVertexArrays;



// tex
extern PFNGLTEXIMAGE3DPROC								glTexImage3D;
extern PFNGLGENERATEMIPMAPPROC							glGenerateMipmap;
extern PFNGLACTIVETEXTUREPROC							glActiveTexture;



// shader program
extern PFNGLCREATEPROGRAMPROC							glCreateProgram;
extern PFNGLDELETEPROGRAMPROC							glDeleteProgram;
extern PFNGLLINKPROGRAMPROC								glLinkProgram;
extern PFNGLUSEPROGRAMPROC								glUseProgram;
extern PFNGLGETPROGRAMIVPROC							glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC						glGetProgramInfoLog;
extern PFNGLVALIDATEPROGRAMPROC							glValidateProgram;

extern PFNGLCREATESHADERPROC							glCreateShader;
extern PFNGLDELETESHADERPROC							glDeleteShader;
extern PFNGLSHADERSOURCEPROC							glShaderSource;
extern PFNGLCOMPILESHADERPROC							glCompileShader;
extern PFNGLATTACHSHADERPROC							glAttachShader;
extern PFNGLDETACHSHADERPROC							glDetachShader;
extern PFNGLGETSHADERIVPROC								glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC						glGetShaderInfoLog;




#include "glext/wglext.h"

// wgl
extern PFNWGLSWAPINTERVALEXTPROC						wglSwapIntervalEXT;

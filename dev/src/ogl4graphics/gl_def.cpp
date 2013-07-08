#include "ogl4graphics_pch.h"
#include "gl_def.h"

PFNGLGETSTRINGIPROC									glGetStringi									= nullptr;

PFNGLCLEARBUFFERFVPROC								glClearBufferfv									= nullptr;
PFNGLCLEARBUFFERFIPROC								glClearBufferfi									= nullptr;


PFNGLGENBUFFERSPROC									glGenBuffers									= nullptr;
PFNGLBINDBUFFERPROC									glBindBuffer									= nullptr;
PFNGLBUFFERDATAPROC									glBufferData									= nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC					glEnableVertexAttribArray						= nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC					glDisableVertexAttribArray						= nullptr;
PFNGLISBUFFERPROC									glIsBuffer										= nullptr;	
PFNGLBUFFERSUBDATAPROC								glBufferSubData									= nullptr;	

PFNGLDELETEBUFFERSPROC								glDeleteBuffers									= nullptr;	
PFNGLVERTEXATTRIBPOINTERPROC						glVertexAttribPointer							= nullptr;	
PFNGLMAPBUFFERRANGEPROC								glMapBufferRange								= nullptr;
PFNGLUNMAPBUFFERPROC								glUnmapBuffer									= nullptr;	
PFNGLBINDVERTEXBUFFERPROC							glBindVertexBuffer								= nullptr;


// debug
PFNGLDEBUGMESSAGECONTROLPROC						glDebugMessageControl							= nullptr;
PFNGLDEBUGMESSAGEINSERTPROC							glDebugMessageInsert							= nullptr;
PFNGLDEBUGMESSAGECALLBACKPROC						glDebugMessageCallback							= nullptr;
PFNGLGETDEBUGMESSAGELOGPROC							glGetDebugMessageLog							= nullptr;




// tex
PFNGLTEXIMAGE3DPROC									glTexImage3D									= nullptr;
PFNGLGENERATEMIPMAPPROC								glGenerateMipmap								= nullptr;
PFNGLACTIVETEXTUREPROC								glActiveTexture									= nullptr;




// VAO
PFNGLGENVERTEXARRAYSPROC							glGenVertexArrays								= nullptr;
PFNGLBINDVERTEXARRAYPROC							glBindVertexArray								= nullptr;
PFNGLDELETEVERTEXARRAYSPROC							glDeleteVertexArrays							= nullptr;



// shader program
PFNGLCREATEPROGRAMPROC								glCreateProgram									= nullptr;
PFNGLDELETEPROGRAMPROC								glDeleteProgram									= nullptr;
PFNGLLINKPROGRAMPROC								glLinkProgram									= nullptr;
PFNGLUSEPROGRAMPROC									glUseProgram									= nullptr;

PFNGLCREATESHADERPROC								glCreateShader									= nullptr;
PFNGLDELETESHADERPROC								glDeleteShader									= nullptr;
PFNGLSHADERSOURCEPROC								glShaderSource									= nullptr;
PFNGLCOMPILESHADERPROC								glCompileShader									= nullptr;
PFNGLATTACHSHADERPROC								glAttachShader									= nullptr;
PFNGLDETACHSHADERPROC								glDetachShader									= nullptr;

PFNGLGETPROGRAMIVPROC								glGetProgramiv									= nullptr;
PFNGLGETPROGRAMINFOLOGPROC							glGetProgramInfoLog								= nullptr;
PFNGLVALIDATEPROGRAMPROC							glValidateProgram								= nullptr;
PFNGLGETSHADERIVPROC								glGetShaderiv									= nullptr;
PFNGLGETSHADERINFOLOGPROC							glGetShaderInfoLog								= nullptr;


// wgl
PFNWGLSWAPINTERVALEXTPROC							wglSwapIntervalEXT								= nullptr;

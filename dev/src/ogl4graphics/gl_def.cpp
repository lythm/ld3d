#include "ogl4graphics_pch.h"
#include "gl_def.h"

PFNGLGETSTRINGIPROC									glGetStringi									= nullptr;



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
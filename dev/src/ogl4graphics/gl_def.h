#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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
extern PFNGLBINDBUFFERRANGEPROC							glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC							glBindBufferBase;


// VAO
extern PFNGLGENVERTEXARRAYSPROC							glGenVertexArrays;	
extern PFNGLBINDVERTEXARRAYPROC							glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC						glDeleteVertexArrays;



// tex
extern PFNGLTEXIMAGE3DPROC								glTexImage3D;
extern PFNGLGENERATEMIPMAPPROC							glGenerateMipmap;
extern PFNGLACTIVETEXTUREPROC							glActiveTexture;
extern PFNGLTEXSTORAGE1DPROC							glTexStorage1D;
extern PFNGLTEXSTORAGE2DPROC							glTexStorage2D;
extern PFNGLTEXSTORAGE3DPROC							glTexStorage3D;
extern PFNGLTEXSUBIMAGE3DPROC							glTexSubImage3D;

// sampler
extern PFNGLGENSAMPLERSPROC								glGenSamplers;
extern PFNGLDELETESAMPLERSPROC							glDeleteSamplers;
extern PFNGLSAMPLERPARAMETERIPROC						glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERFPROC						glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERIVPROC						glSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFVPROC						glSamplerParameterfv;
extern PFNGLBINDSAMPLERPROC								glBindSampler;


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

extern PFNGLGETUNIFORMBLOCKINDEXPROC					glGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC						glUniformBlockBinding;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC					glGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC				glGetActiveUniformBlockName;
extern PFNGLGETACTIVEUNIFORMSIVPROC						glGetActiveUniformsiv;
extern PFNGLGETUNIFORMLOCATIONPROC						glGetUniformLocation;

extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC					glProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORM1FPROC						glProgramUniform1f;
extern PFNGLPROGRAMUNIFORM1IPROC						glProgramUniform1i;
extern PFNGLPROGRAMUNIFORM1UIPROC						glProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM2FVPROC						glProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM3FVPROC						glProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM4FVPROC						glProgramUniform4fv;
extern PFNGLPROGRAMUNIFORM2IVPROC						glProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM3IVPROC						glProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM4IVPROC						glProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM2UIVPROC						glProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3UIVPROC						glProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4UIVPROC						glProgramUniform4uiv;



// render buffer
extern PFNGLGENRENDERBUFFERSPROC						glGenRenderbuffers;
extern PFNGLDELETERENDERBUFFERSPROC						glDeleteRenderbuffers;
extern PFNGLRENDERBUFFERSTORAGEPROC						glRenderbufferStorage;
extern PFNGLBINDRENDERBUFFERPROC						glBindRenderbuffer;




#include "glext/wglext.h"

// wgl
extern PFNWGLSWAPINTERVALEXTPROC						wglSwapIntervalEXT;

#pragma once


#ifdef __APPLE__
//#include <OpenGL/OpenGL.h>
//#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/gl3.h>
#endif


#if defined(_WIN64) || defined(_WIN32)
#include "glext/glcorearb.h"

extern PFNGLGETERRORPROC								glGetError;
extern PFNGLGETSTRINGPROC								glGetString;
extern PFNGLGETINTEGERVPROC								glGetIntegerv;
extern PFNGLDELETETEXTURESPROC							glDeleteTextures;

extern PFNGLGENTEXTURESPROC								glGenTextures;
extern PFNGLBINDTEXTUREPROC								glBindTexture;
extern PFNGLTEXPARAMETERIPROC							glTexParameteri;
extern PFNGLTEXSUBIMAGE1DPROC							glTexSubImage1D;
extern PFNGLTEXSUBIMAGE2DPROC							glTexSubImage2D;
extern PFNGLTEXSUBIMAGE3DPROC							glTexSubImage3D;

extern PFNGLENABLEPROC									glEnable;
extern PFNGLDISABLEPROC									glDisable;

extern PFNGLCOLORMASKPROC								glColorMask;

extern PFNGLPOLYGONMODEPROC								glPolygonMode;

extern PFNGLCULLFACEPROC								glCullFace;
extern PFNGLFRONTFACEPROC								glFrontFace;
extern PFNGLPOLYGONOFFSETPROC							glPolygonOffset;
extern PFNGLDEPTHMASKPROC								glDepthMask;
extern PFNGLDEPTHFUNCPROC								glDepthFunc;

extern PFNGLDRAWARRAYSPROC								glDrawArrays;
extern PFNGLDRAWELEMENTSPROC							glDrawElements;
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC				glMultiDrawElementsBaseVertex;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC					glDrawElementsBaseVertex;


extern PFNGLVIEWPORTPROC								glViewport;


extern PFNGLGETSTRINGIPROC								glGetStringi;



extern PFNGLCLEARBUFFERFVPROC							glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC							glClearBufferfi;
extern PFNGLCLEARBUFFERIVPROC							glClearBufferiv;


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
extern PFNGLVERTEXATTRIBIPOINTERPROC					glVertexAttribIPointer;
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
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC					glTexStorage2DMultisample;
extern PFNGLTEXSTORAGE3DPROC							glTexStorage3D;
extern PFNGLTEXSUBIMAGE3DPROC							glTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC					glCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC					glCompressedTexSubImage3D;

// sampler
extern PFNGLGENSAMPLERSPROC								glGenSamplers;
extern PFNGLDELETESAMPLERSPROC							glDeleteSamplers;
extern PFNGLSAMPLERPARAMETERIPROC						glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERFPROC						glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERIVPROC						glSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFVPROC						glSamplerParameterfv;
extern PFNGLBINDSAMPLERPROC								glBindSampler;
extern PFNGLGETSAMPLERPARAMETERIVPROC					glGetSamplerParameteriv;


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
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC			glRenderbufferStorageMultisample;
extern PFNGLBINDRENDERBUFFERPROC						glBindRenderbuffer;

// fbo
extern PFNGLGENFRAMEBUFFERSPROC							glGenFramebuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC						glDeleteFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC							glBindFramebuffer;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC					glCheckFramebufferStatus;
extern PFNGLFRAMEBUFFERTEXTUREPROC						glFramebufferTexture;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC					glFramebufferRenderbuffer;
extern PFNGLDRAWBUFFERSPROC								glDrawBuffers;

// render state
extern PFNGLBLENDCOLORPROC								glBlendColor;
extern PFNGLBLENDEQUATIONSEPARATEPROC					glBlendEquationSeparate;
extern PFNGLBLENDFUNCSEPARATEPROC						glBlendFuncSeparate;
extern PFNGLSTENCILOPSEPARATEPROC						glStencilOpSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC						glStencilMaskSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC						glStencilFuncSeparate;


extern PFNGLWAITSYNCPROC								glWaitSync;
#endif

#if defined(_WIN64) || defined(_WIN32)
#include "glext/wglext.h"

// wgl
extern PFNWGLSWAPINTERVALEXTPROC						wglSwapIntervalEXT;


#endif

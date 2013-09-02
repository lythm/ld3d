#include "ogl4graphics_pch.h"
#include "gl_def.h"

#if defined(_WIN64) || defined(_WIN32)




PFNGLGETSTRINGPROC								glGetString											= nullptr;
PFNGLGETINTEGERVPROC							glGetIntegerv										= nullptr;
PFNGLDELETETEXTURESPROC							glDeleteTextures									= nullptr;

PFNGLGENTEXTURESPROC							glGenTextures										= nullptr;
PFNGLBINDTEXTUREPROC							glBindTexture										= nullptr;
PFNGLTEXPARAMETERIPROC							glTexParameteri										= nullptr;
PFNGLTEXSUBIMAGE1DPROC							glTexSubImage1D										= nullptr;
PFNGLTEXSUBIMAGE2DPROC							glTexSubImage2D										= nullptr;
PFNGLTEXSUBIMAGE3DPROC							glTexSubImage3D										= nullptr;

PFNGLENABLEPROC									glEnable											= nullptr;
PFNGLDISABLEPROC								glDisable											= nullptr;

PFNGLCOLORMASKPROC								glColorMask											= nullptr;

PFNGLPOLYGONMODEPROC							glPolygonMode										= nullptr;

PFNGLCULLFACEPROC								glCullFace											= nullptr;
PFNGLFRONTFACEPROC								glFrontFace											= nullptr;
PFNGLPOLYGONOFFSETPROC							glPolygonOffset										= nullptr;
PFNGLDEPTHMASKPROC								glDepthMask											= nullptr;
PFNGLDEPTHFUNCPROC								glDepthFunc											= nullptr;


PFNGLDRAWARRAYSPROC								glDrawArrays										= nullptr;
PFNGLDRAWELEMENTSPROC							glDrawElements										= nullptr;
PFNGLVIEWPORTPROC								glViewport											= nullptr;









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
PFNGLBINDBUFFERRANGEPROC							glBindBufferRange								= nullptr;
PFNGLBINDBUFFERBASEPROC								glBindBufferBase								= nullptr;


// debug
PFNGLDEBUGMESSAGECONTROLPROC						glDebugMessageControl							= nullptr;
PFNGLDEBUGMESSAGEINSERTPROC							glDebugMessageInsert							= nullptr;
PFNGLDEBUGMESSAGECALLBACKPROC						glDebugMessageCallback							= nullptr;
PFNGLGETDEBUGMESSAGELOGPROC							glGetDebugMessageLog							= nullptr;




// tex
PFNGLTEXIMAGE3DPROC									glTexImage3D									= nullptr;
PFNGLGENERATEMIPMAPPROC								glGenerateMipmap								= nullptr;
PFNGLACTIVETEXTUREPROC								glActiveTexture									= nullptr;
PFNGLTEXSTORAGE1DPROC								glTexStorage1D									= nullptr;
PFNGLTEXSTORAGE2DPROC								glTexStorage2D									= nullptr;
PFNGLTEXSTORAGE3DPROC								glTexStorage3D									= nullptr;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC					glCompressedTexSubImage2D						= nullptr;
// sampler
PFNGLGENSAMPLERSPROC								glGenSamplers									= nullptr;
PFNGLDELETESAMPLERSPROC								glDeleteSamplers								= nullptr;
PFNGLSAMPLERPARAMETERIPROC							glSamplerParameteri								= nullptr;
PFNGLSAMPLERPARAMETERFPROC							glSamplerParameterf								= nullptr;
PFNGLSAMPLERPARAMETERIVPROC							glSamplerParameteriv							= nullptr;
PFNGLSAMPLERPARAMETERFVPROC							glSamplerParameterfv							= nullptr;
PFNGLBINDSAMPLERPROC								glBindSampler									= nullptr;



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

PFNGLGETUNIFORMBLOCKINDEXPROC						glGetUniformBlockIndex							= nullptr;
PFNGLUNIFORMBLOCKBINDINGPROC						glUniformBlockBinding							= nullptr;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC					glGetActiveUniformBlockiv						= nullptr;
PFNGLGETACTIVEUNIFORMSIVPROC						glGetActiveUniformsiv							= nullptr;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC					glGetActiveUniformBlockName						= nullptr;
PFNGLGETUNIFORMLOCATIONPROC							glGetUniformLocation							= nullptr;


PFNGLPROGRAMUNIFORM1FPROC							glProgramUniform1f								= nullptr;
PFNGLPROGRAMUNIFORM1IPROC							glProgramUniform1i								= nullptr;
PFNGLPROGRAMUNIFORM1UIPROC							glProgramUniform1ui								= nullptr;
	
PFNGLPROGRAMUNIFORM2FVPROC							glProgramUniform2fv								= nullptr;
PFNGLPROGRAMUNIFORM3FVPROC							glProgramUniform3fv								= nullptr;
PFNGLPROGRAMUNIFORM4FVPROC							glProgramUniform4fv								= nullptr;
	
PFNGLPROGRAMUNIFORM2IVPROC							glProgramUniform2iv								= nullptr;
PFNGLPROGRAMUNIFORM3IVPROC							glProgramUniform3iv								= nullptr;
PFNGLPROGRAMUNIFORM4IVPROC							glProgramUniform4iv								= nullptr;
	
PFNGLPROGRAMUNIFORM2UIVPROC							glProgramUniform2uiv							= nullptr;
PFNGLPROGRAMUNIFORM3UIVPROC							glProgramUniform3uiv							= nullptr;
PFNGLPROGRAMUNIFORM4UIVPROC							glProgramUniform4uiv							= nullptr;

PFNGLPROGRAMUNIFORMMATRIX4FVPROC					glProgramUniformMatrix4fv						= nullptr;



// render buffer

PFNGLGENRENDERBUFFERSPROC							glGenRenderbuffers								= nullptr;
PFNGLDELETERENDERBUFFERSPROC						glDeleteRenderbuffers							= nullptr;
PFNGLRENDERBUFFERSTORAGEPROC						glRenderbufferStorage							= nullptr;
PFNGLBINDRENDERBUFFERPROC							glBindRenderbuffer								= nullptr;

// fbo
PFNGLGENFRAMEBUFFERSPROC							glGenFramebuffers								= nullptr;
PFNGLDELETEFRAMEBUFFERSPROC							glDeleteFramebuffers							= nullptr;
PFNGLBINDFRAMEBUFFERPROC							glBindFramebuffer								= nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSPROC						glCheckFramebufferStatus						= nullptr;
PFNGLFRAMEBUFFERTEXTUREPROC							glFramebufferTexture							= nullptr;
PFNGLFRAMEBUFFERRENDERBUFFERPROC					glFramebufferRenderbuffer						= nullptr;
PFNGLDRAWBUFFERSPROC								glDrawBuffers									= nullptr;


// render state
PFNGLBLENDCOLORPROC									glBlendColor									= nullptr;
PFNGLBLENDEQUATIONSEPARATEPROC						glBlendEquationSeparate							= nullptr;
PFNGLBLENDFUNCSEPARATEPROC							glBlendFuncSeparate								= nullptr;
PFNGLSTENCILOPSEPARATEPROC							glStencilOpSeparate								= nullptr;
PFNGLSTENCILMASKSEPARATEPROC						glStencilMaskSeparate							= nullptr;
PFNGLSTENCILFUNCSEPARATEPROC						glStencilFuncSeparate							= nullptr;

#endif

#if defined(_WIN64) || defined(_WIN32)
// wgl
PFNWGLSWAPINTERVALEXTPROC							wglSwapIntervalEXT								= nullptr;
#endif


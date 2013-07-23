#version 330

uniform _MATRIX
{
	mat4	MATRIX_WORLD;	
	mat4	MATRIX_VIEW;	
	mat4	MATRIX_PROJ;	

	mat4	MATRIX_I_WORLD;
	mat4	MATRIX_I_VIEW;	
	mat4	MATRIX_I_PROJ;	

	mat4	MATRIX_WV;		
	mat4	MATRIX_WVP;	

	mat4	MATRIX_I_WV;	
	mat4	MATRIX_I_WVP;	
	mat4	MATRIX_I_VP;	

};

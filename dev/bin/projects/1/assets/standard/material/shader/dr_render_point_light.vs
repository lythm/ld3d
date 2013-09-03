#version 330

#pragma include "matrix_block.glsl"


layout(location = 0) in vec3 pos;

void main()
{
	gl_Position = vec4(pos, 1) * MATRIX_WVP;
}

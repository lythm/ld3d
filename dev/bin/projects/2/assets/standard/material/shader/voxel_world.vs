#version 330

#pragma include "matrix_block.glsl"

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 clr;


smooth out vec3 v_normal;
smooth out vec4 f_color;


void main()
{
	gl_Position = vec4(pos, 1) * MATRIX_WVP;
	v_normal = (vec4(normal, 0) * MATRIX_WV).xyz;
	f_color = clr;
}

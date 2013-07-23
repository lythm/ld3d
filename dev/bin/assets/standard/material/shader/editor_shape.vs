#version 330




#pragma include "matrix_block.glsl"
layout(row_major) uniform;


layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

out vec4 p_normal;

void main()
{
	gl_Position = vec4(pos.xyz, 1) * MATRIX_WVP;

	p_normal = vec4(normal.xyz, 0) * MATRIX_WVP;
}

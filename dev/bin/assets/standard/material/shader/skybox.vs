#version 330
#pragma include "matrix_block.glsl"

layout(location = 0) in vec3 pos;

out vec3 v_pos;

void main()
{
	v_pos = (vec4(pos, 1) * MATRIX_WV).xyz;
	gl_Position = vec4(pos, 1) * MATRIX_WVP;
}

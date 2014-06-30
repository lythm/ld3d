#version 330

#pragma include "../../../standard/material/shader/matrix_block.glsl"

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 uv;
layout(location = 3) in float ao;

smooth out vec3 v_normal;
smooth out vec3 tex_coord;
smooth out float v_ao;

void main()
{
	gl_Position = vec4(pos.xyz, 1) * MATRIX_WVP;
	v_normal = (vec4(normal.xyz, 0) * MATRIX_WV).xyz;
	v_ao = ao;
	tex_coord = uv;
}

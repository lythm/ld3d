#version 330

#pragma include "../../../standard/material/shader/matrix_block.glsl"

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;


smooth out vec3 v_normal;
smooth out vec2 tex_coord;


void main()
{
	gl_Position = vec4(pos.xyz, 1) * MATRIX_WVP;
	v_normal = (vec4(normal.xyz, 0) * MATRIX_WV).xyz;
	tex_coord = uv;
}

#version 330

#pragma include "../../../standard/material/shader/matrix_block.glsl"

layout(location = 0) in vec3			pos;
layout(location = 1) in vec2			uv;
layout(location = 2) in int				tid;
layout(location = 3) in float			ao;
layout(location = 4) in int				normal;

smooth out vec3							v_normal;
smooth out vec2							tex_coord;
flat out int							tex_id;
smooth out float						v_ao;

const vec3 n_map[6] = vec3[6]
(
	vec3(-1, 0, 0),
	vec3(1, 0, 0),

	vec3(0, -1, 0),
	vec3(0, 1, 0),

	vec3(0, 0, -1),
	vec3(0, 0, 1)
);
vec3 decodeNormal(int n)
{
	return n_map[n];
}

void main()
{

	gl_Position				= vec4(pos.xyz, 1) * MATRIX_WVP;

	vec3 decoded_normal		= decodeNormal(normal);
	
	v_normal				= (vec4(decoded_normal.xyz, 0) * MATRIX_WV).xyz;
	v_ao					= ao;
	tex_id					= tid;
	tex_coord				= uv;
}

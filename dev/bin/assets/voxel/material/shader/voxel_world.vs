#version 330

#pragma include "../../../standard/material/shader/matrix_block.glsl"

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 uv;
layout(location = 2) in float ao;
layout(location = 3) in float normal;

smooth out vec3 v_normal;
smooth out vec3 tex_coord;
smooth out float v_ao;

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

	gl_Position = vec4(pos.xyz, 1) * MATRIX_WVP;

	//vec3 decoded_normal = decodeNormal(normal);

//	vec3 decoded_normal = n_map[normal];

	vec3 decoded_normal = vec3(0, 0, 0);

	v_ao = ao;
	if(normal == 0)
	{
		decoded_normal.x = -1;
		//v_ao = ao;
	}
	if(normal == 1)
	{
		decoded_normal.x = 1;
		
	}
	if(normal == 2)
	{
		decoded_normal.y = -1;
		
	}
	if(normal == 3)
	{
		decoded_normal.y = 1;
		
	}
	if(normal == 4)
	{
		decoded_normal.z = -1;
		
	}
	if(normal == 5)
	{
		decoded_normal.z = 1;
		
	}


	//decoded_normal = vec3(0, 1, 0);
	
	v_normal = (vec4(decoded_normal.xyz, 0) * MATRIX_WV).xyz;
//	v_ao = ao;
//	v_ao = 1.0f;

	tex_coord = uv;
}

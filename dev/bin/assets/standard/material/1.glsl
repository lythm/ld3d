#version 330

layout(row_major) uniform;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
uniform mat4 v;
uniform mat4 p;



out vec2 tex_coord;
void main()
{
	vec4 o_pos = vec4(pos, 1);
	o_pos *= v;
	o_pos *= p;

	gl_Position = o_pos;

	tex_coord = vec2(uv.x, 1- uv.y);
	//tex_coord = uv;
}


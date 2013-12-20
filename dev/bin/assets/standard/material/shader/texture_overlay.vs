#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;


layout(row_major) uniform;

uniform vec2 screen_size;
uniform vec4 overlay_rect;

uniform mat4 trans;

out vec2 f_uv;

void main()
{
	f_uv = uv;
	vec3 p = pos;

	p = (vec4(p, 1) * trans).xyz;

	p.x = (p.x / screen_size.x) * 2 - 1; 
	p.y = (1 - p.y / screen_size.y) * 2 - 1;

	p.z = 0;

	gl_Position = vec4(p, 1);
}

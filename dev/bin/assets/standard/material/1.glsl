#version 330

layout(row_major) uniform;

layout(location = 0) in vec3 pos;

layout(std140) uniform mat
{
	mat4 view;
	mat4 proj;
	mat4 world;
};


layout(std140, row_major) uniform dummy1
{
	float d1;

};

layout(std140, row_major) uniform dummy2
{
	int d2;
};

uniform mat4 v;
uniform mat4 p;

out vec4 f_color;
void main()
{
	vec4 o_pos = vec4(pos, 1);
	o_pos *= v;
	o_pos *= p;

	gl_Position = o_pos;

	f_color = vec4(0.5, 0, 0.5, 1);
}


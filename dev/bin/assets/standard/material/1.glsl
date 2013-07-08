#version 330

layout(location = 0) in vec3 pos;

out vec4 f_color;
void main()
{
	gl_Position = vec4(pos, 1);
	f_color = vec4(0.5, 0, 0.5, 1);
}


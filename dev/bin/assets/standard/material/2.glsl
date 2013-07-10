
#version 330

in vec2 tex_coord;
out vec4 o_color;

uniform sampler2D base;

void main()
{
	o_color = texture2D(base, tex_coord.st);
}


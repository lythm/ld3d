#version 330
#pragma include "../../../standard/material/shader/matrix_block.glsl"

layout(location = 0) in vec3 pos;

uniform vec3 world_pos;

smooth out vec3 v_clr;

vec3 sun_pos = vec3(0, 0.5, 1);
vec3 sky_color(vec3 dir)
{
	sun_pos = normalize(sun_pos);
	float d = (1 + 2 * dot(dir, sun_pos)) / 3;
	return vec3(0.3, 0.3, 0.6) * d;// * vec3(0.7, 0.8, 1.0);
}

void main()
{

	

	
	vec3 v = pos - vec3(0, 0, 0);

	v = normalize(v);

	gl_Position = vec4(pos + world_pos, 1) * MATRIX_VIEW * MATRIX_PROJ;

	v_clr = sky_color(v);
}

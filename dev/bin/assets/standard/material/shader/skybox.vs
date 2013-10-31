#version 330
#pragma include "matrix_block.glsl"

layout(location = 0) in vec3 pos;

uniform vec3 world_pos;

out vec3 sky_map_uvw;

void main()
{
	sky_map_uvw = (vec4(pos, 1) * MATRIX_WV).xyz;
	sky_map_uvw = normalize(sky_map_uvw);
	gl_Position = vec4(pos + world_pos, 1) * MATRIX_VIEW * MATRIX_PROJ;
}

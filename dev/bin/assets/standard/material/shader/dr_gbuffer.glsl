#version 330

// layout(location = 0) out float	G_BUFFER_0;
// layout(location = 1) out vec2	G_BUFFER_1;
// layout(location = 2) out vec4	G_BUFFER_2;
void dr_gbuffer_compose(float depth, vec2 normal_xy, vec3 diffuse, float specular)
{
	G_BUFFER_0 = depth;
	G_BUFFER_1 = normal_xy;
	G_BUFFER_2 = vec4(diffuse, specular);
}

float dr_gbuffer_get_depth(sampler2D g[3], vec2 uv)
{
	float d = texture(g[0], uv).r;
	return d;
}

vec3 dr_gbuffer_get_normal(sampler2D g[3], vec2 uv)
{
	vec3 normal;
	
	normal.xy = texture(g[1], uv).xy;
	normal.z = -sqrt(1-dot(normal.xy, normal.xy));
	return normalize(normal);
}

vec4 dr_gbuffer_get_albedo(sampler2D g[3], vec2 uv)
{
	vec4 c = texture(g[2], uv);
	return c;
}


float depth_2_view_space_z(float z, mat4 proj)
{
	return proj[3][2] / (z - proj[2][2]);
}

vec2 view_port_2_screen_space(vec2 vp, mat4 proj, vec2 dim)
{
	vec2 screenPixelOffset = vec2(2.0f, -2.0f) / dim;
    return (vp * screenPixelOffset.xy + vec2(-1.0f, 1.0f));
}

vec3 view_port_2_view_space(vec2 vp, float view_z, mat4 proj, vec2 dim)
{
	vec2 screen = view_port_2_screen_space(vp, proj, dim);
	vec2 v_ray = vec2(screen.x / proj[0][0],
							screen.y / proj[1][1]);

	vec3 view = vec3(v_ray, view_z);
	
	view.xy = view.xy * view.z;

	return view;
}

vec2 screenpos_2_uv(vec4 spos)
{
	vec2 uv = spos.xy / spos.w;
	
	uv.x = uv.x * 0.5 + 0.5;
	uv.y = 1 - (uv.y * 0.5 + 0.5);
	return uv;
}

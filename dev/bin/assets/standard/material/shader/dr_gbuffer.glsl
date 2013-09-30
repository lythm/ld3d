#version 330

vec3 decode_normal(vec2 n)
{
	vec3 normal;
	
	normal.z = (n.x * n.x + n.y * n.y) * 2 - 1;

	normal.xy = normalize(n.xy) * sqrt( 1 - normal.z * normal.z);

	return normalize(normal);
}

vec2 encode_normal(vec3 n)
{
	return normalize(n.xy) * sqrt(n.z * 0.5 + 0.5);
}

float dr_gbuffer_get_depth(sampler2D g, vec2 uv)
{
	float d = texture(g, uv);
	return d;
}

vec3 dr_gbuffer_get_normal(sampler2D g, vec2 uv)
{
	return decode_normal(texture(g, uv).xy);
}

vec4 dr_gbuffer_get_albedo(sampler2D g, vec2 uv)
{
	vec4 c = texture(g, uv);
	return c;
}


vec2 view_port_2_screen_space(vec2 vp, mat4 proj, vec2 dim)
{
	return (vp / dim) * vec2(2, 2) + vec2(-1, -1);
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

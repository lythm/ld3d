struct GBuffer
{
	float	T1:SV_TARGET0;
	float2	T2:SV_TARGET1;
	float4	T3:SV_TARGET2;
};



SamplerState Sampler_GBuffer
{
	AddressU = wrap;
	AddressV = wrap;

	filter = MIN_MAG_MIP_LINEAR ;
	BorderColor = float4(1,0,0,1);
	MinLod = 0;
	MaxLod = 0;
};


GBuffer dr_gbuffer_compose(float depth, float2 normal_xy, float3 diffuse, float specular)
{
	GBuffer g;
	g.T1 = depth;
	g.T2 = normal_xy;
	g.T3 = float4(diffuse, specular);

	return g;
}
float dr_gbuffer_get_depth(Texture2D g[3], float2 uv)
{
	float d = g[0].Sample(Sampler_GBuffer, uv).r;

	return d;
}
float3 dr_gbuffer_get_normal(Texture2D g[3], float2 uv)
{
	float3 normal = float3(g[1].Sample(Sampler_GBuffer, uv).xy, 0);
	
	normal.z = -sqrt(1-dot(normal.xy, normal.xy));
	normal = normalize(normal);
	
	return normal;
}

float4 dr_gbuffer_get_albedo(Texture2D g[3], float2 uv)
{
	float4 c = g[2].Sample(Sampler_GBuffer, uv);
	return c;
}


float depth_2_view_space_z(float z, float4x4 proj)
{
	return proj._43 / (z - proj._33);
}

float2 view_port_2_screen_space(float2 vp, float4x4 proj, float2 dim)
{
	float2 screenPixelOffset = float2(2.0f, -2.0f) / dim;
    return (vp * screenPixelOffset.xy + float2(-1.0f, 1.0f));
}

float3 view_port_2_view_space(float2 vp, float view_z, float4x4 proj, float2 dim)
{
	float2 screen = view_port_2_screen_space(vp, proj, dim);
	float2 v_ray = float2(screen.x / proj._11,
							screen.y / proj._22);

	float3 view = float3(v_ray, view_z);
	
	view.xy = view.xy * view.z;

	return view;
}

float2 screenpos_2_uv(float4 spos)
{
	float2 uv = spos.xy / spos.w;
	
	uv.x = uv.x * 0.5 + 0.5;
	uv.y = 1 - (uv.y * 0.5 + 0.5);
	return uv;
}

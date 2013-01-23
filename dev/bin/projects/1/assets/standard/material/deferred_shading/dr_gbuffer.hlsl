struct GBuffer
{
	float	T1:SV_TARGET0;
	float2	T2:SV_TARGET1;
	float4	T3:SV_TARGET2;
};



SamplerState Sampler_GBuffer
{
	AddressU = clamp;
	AddressV = clamp;

	filter = MIN_MAG_MIP_LINEAR ;
	BorderColor = float4(1,0,0,1);
	MinLod = 0;
	MaxLod = 0;
};
SamplerState Sampler_GBufferNormal
{
	AddressU = clamp;
	AddressV = clamp;

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
	float3 normal = float3(g[1].Sample(Sampler_GBufferNormal, uv).xy, 0);
	
	normal.z = -sqrt(1-dot(normal.xy, normal.xy));
	normal = normalize(normal);
	
	return normal;
}

float3 dr_gbuffer_get_position(Texture2D g[3], float2 uv, float2 spos_xy)
{
	float3 p;
	p.z = dr_gbuffer_get_depth(g, uv);
	p.xy = spos_xy;

	return p;
}
float3 dr_gbuffer_get_diffuse(Texture2D g[3], float2 uv)
{
	float4 c = g[2].Sample(Sampler_GBuffer, uv);
	return c.xyz;
}
float dr_gbuffer_get_specular_power(Texture2D<half4> g[3], float2 uv)
{
	float4 c = g[2].Sample(Sampler_GBuffer, uv);
	return c.w;
}


float2 dr_gbuffer_screenpos_2_uv(float4 spos)
{
	float2 uv = spos.xy / spos.w;
	
	uv.x = uv.x * 0.5 + 0.5;
	uv.y = 1 - (uv.y * 0.5 + 0.5);
	return uv;
}
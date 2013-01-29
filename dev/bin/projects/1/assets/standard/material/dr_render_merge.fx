#include <deferred_shading/dr_gbuffer.hlsl>

float4x4 mat:MATRIX_WVP;
float4x4 matView:MATRIX_WV;

Texture2D tex_gbuffer[3]:DR_GBUFFER;
Texture2D<float4> tex_abuffer:DR_ABUFFER;


struct vs_in
{
	float3 pos:POSITION;
};
struct vs_out
{
	float4 pos:SV_POSITION;
};

vs_out vs_main(vs_in i)
{
	vs_out o;
	i.pos.z = 1;
	o.pos = float4(i.pos.xyz, 1);
	return o;
}

struct ps_out
{
	float4 color:SV_TARGET;
};

ps_out ps_main(vs_out i)
{
	ps_out o;
	float2 dim;
	tex_abuffer.GetDimensions(dim.x, dim.y);
	float2 uv = i.pos.xy / dim;

	float4 d = dr_gbuffer_get_albedo(tex_gbuffer, uv);
	float4 l = tex_abuffer.Sample(Sampler_GBuffer,uv);

	o.color.xyz = l.xyz * d.xyz + (l.w * d.xyz) * d.w;
	o.color.w = 1;

	//o.color.xyz = dr_gbuffer_get_depth(tex_gbuffer, uv) / 100;
	return o;
}
RasterizerState rs
{
	CULLMODE				= Back;
};
DepthStencilState ds
{
	DepthEnable						= true;
	DepthFunc						= GREATER;
	DepthWriteMask					= ZERO;
	StencilEnable					= false;
	
};
BlendState bs
{
	BLENDENABLE[0]				= false;
	
};
technique11 test
{
  pass p1
  {
	SetBlendState( bs, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
	SetRasterizerState(rs);
	SetDepthStencilState(ds, 1);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main() ) );

  }
}

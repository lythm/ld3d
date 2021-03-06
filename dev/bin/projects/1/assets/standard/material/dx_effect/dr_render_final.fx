#include <deferred_shading/dr_gbuffer.hlsl>

Texture2D<float4> post_output;


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
	post_output.GetDimensions(dim.x, dim.y);
	
	float2 uv = i.pos.xy / dim;

	o.color = float4(post_output.Sample(Sampler_GBuffer, uv).xyz, 1);


	//o.color = float4(1, 1, 1, 1);
	return o;
}
RasterizerState rs
{
	CULLMODE						= Back;
};
DepthStencilState ds
{
	DepthEnable						= FALSE;
	DepthFunc						= LESS;
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

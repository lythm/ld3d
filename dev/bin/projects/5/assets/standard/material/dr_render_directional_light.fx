#include <deferred_shading/dr_gbuffer.hlsl>
#include <deferred_shading/dr_light.hlsl>

Texture2D tex_gbuffer[3]:DR_GBUFFER;
float4x4 wvp:MATRIX_WVP;
float4x4 wv:MATRIX_WV;
float4x4 ip:MATRIX_I_PROJ;

DirectionalLight	light;

struct INPUT
{
	float3 pos:POSITION;
};
struct PS_INPUT
{
	float4 pos:SV_POSITION;
};
struct PS_OUTPUT
{
	float4 clr:SV_TARGET;
};
PS_INPUT vs_dirlight_main(INPUT i)
{
	PS_INPUT o;
	
	i.pos.z = 1;

	o.pos = float4(i.pos, 1);

	return o;
}
PS_OUTPUT ps_dirlight_main(PS_INPUT i)
{
	PS_OUTPUT o;
	
	float2 dim;
	tex_gbuffer[0].GetDimensions(dim.x, dim.y);
	
	float2 uv = i.pos.xy / dim;

	float3 n = dr_gbuffer_get_normal(tex_gbuffer, uv);

	LightResult ret = dr_light_dir(n, light, wv);
	o.clr.xyz = ret.diffuse;
	o.clr.w = rgb_2_il(ret.specular);

	//o.clr.xyz = float3(1, 1, 1);
	return o;
}

DepthStencilState DS_DirLight
{
	DepthEnable						= true;
	DepthFunc						= GREATER;
	DepthWriteMask					= ZERO;
	StencilEnable					= false;
};
RasterizerState RS_DirLight
{
	CULLMODE = back;
};

BlendState BS_DirLight
{
	ALPHATOCOVERAGEENABLE				= false;
	BLENDENABLE[0]						= true;
	SRCBLEND							= ONE;
	DESTBLEND							= ONE;
	BLENDOP								= ADD;
	SRCBLENDALPHA						= ONE;
	DESTBLENDALPHA						= ONE;
	BLENDOPALPHA						= ADD;
	RENDERTARGETWRITEMASK[0]			= 0xF;
};




technique11 dir_light
{
	pass p1
	{
		SetBlendState( BS_DirLight, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(RS_DirLight);
		SetDepthStencilState(DS_DirLight, 1);
		SetVertexShader( CompileShader( vs_4_0, vs_dirlight_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_dirlight_main()));
	}
}


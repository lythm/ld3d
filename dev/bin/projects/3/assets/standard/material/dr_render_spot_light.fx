#include <deferred_shading/dr_gbuffer.hlsl>
#include <deferred_shading/dr_light.hlsl>

Texture2D tex_gbuffer[3]:DR_GBUFFER;
float4x4 wvp:MATRIX_WVP;
float4x4 wv:MATRIX_WV;
float4x4 i_p:MATRIX_I_PROJ;
float4x4 p:MATRIX_PROJ;
SpotLight	light;

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
PS_INPUT vs_main(INPUT i)
{
	PS_INPUT o;
	
	o.pos = mul(float4(i.pos, 1), wvp);
	return o;
}



PS_OUTPUT ps_main(PS_INPUT i)
{
	PS_OUTPUT o;
	
	float2 dim;
    tex_gbuffer[0].GetDimensions(dim.x, dim.y);

	float2 uv = i.pos.xy / dim;

	float3 n = dr_gbuffer_get_normal(tex_gbuffer, uv);
	float depth = dr_gbuffer_get_depth(tex_gbuffer, uv);
	float3 v_pos = view_port_2_view_space(i.pos.xy, depth, p, dim);

	LightResult ret =  dr_light_spot(v_pos, n, light, wv);
	o.clr.xyz = ret.diffuse;
	o.clr.w = rgb_2_il(ret.specular);

	return o;
}

RasterizerState RS_SpotLight_StencilPass
{
	CULLMODE = Back;
};

BlendState BS_SpotLight_StencilPass
{
	ALPHATOCOVERAGEENABLE				= false;
	BLENDENABLE[0]						= false;
};


DepthStencilState DS_SpotLight_StencilPass
{
	DepthEnable						= true;
	DepthFunc						= LESS_EQUAL;
	DepthWriteMask					= ZERO;
	StencilEnable					= true;
	FrontFaceStencilFail			= KEEP;
	FrontFaceStencilDepthFail		= REPLACE;
	FrontFaceStencilPass			= KEEP;
	FrontFaceStencilFunc			= ALWAYS;
};

RasterizerState RS_SpotLight
{
	CULLMODE = front;
};

BlendState BS_SpotLight
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


DepthStencilState DS_SpotLight
{
	DepthEnable						= true;
	DepthFunc						= GREATER;
	DepthWriteMask					= ZERO;
	StencilEnable					= true;

	BackFaceStencilFail				= KEEP;
	BackFaceStencilDepthFail		= KEEP;
	BackFaceStencilPass				= KEEP;
	BackFaceStencilFunc				= EQUAL;
};







technique11 deferred
{
	pass p1
	{
		SetBlendState( BS_SpotLight_StencilPass, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(RS_SpotLight_StencilPass);
		SetDepthStencilState(DS_SpotLight_StencilPass, 1);
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( NULL);
	}

	pass p2
	{
		SetBlendState( BS_SpotLight, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(RS_SpotLight);
		SetDepthStencilState(DS_SpotLight, 0);
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_main()));
	}
}


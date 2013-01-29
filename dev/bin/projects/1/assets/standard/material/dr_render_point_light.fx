#include <deferred_shading/dr_gbuffer.hlsl>
#include <deferred_shading/dr_light.hlsl>

Texture2D tex_gbuffer[3]:DR_GBUFFER;
float4x4 wvp:MATRIX_WVP;
float4x4 wv:MATRIX_WV;
float4x4 i_p:MATRIX_I_PROJ;
float4x4 p:MATRIX_PROJ;
PointLight	light;

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

	LightResult ret = dr_light_point(v_pos, n, light, wv);
	o.clr.xyz = ret.diffuse;
	o.clr.w = rgb_2_il(ret.specular);

//	o.clr = float4(1, 1, 1, 1);
	return o;
}



RasterizerState RS_PointLight_StencilPass
{
	CULLMODE = Back;
};

BlendState BS_PointLight_StencilPass
{
	ALPHATOCOVERAGEENABLE				= false;
	BLENDENABLE[0]						= false;
};


DepthStencilState DS_PointLight_StencilPass
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

RasterizerState RS_PointLight
{
	CULLMODE = front;
};

BlendState BS_PointLight
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


DepthStencilState DS_PointLight
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



technique11 point_light
{
	pass p1
	{
		SetBlendState( BS_PointLight_StencilPass, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(RS_PointLight_StencilPass);
		SetDepthStencilState(DS_PointLight_StencilPass, 1);
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( NULL);
	}

	pass p2
	{
		SetBlendState( BS_PointLight, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(RS_PointLight);
		SetDepthStencilState(DS_PointLight, 0);
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_main()));
	}
}


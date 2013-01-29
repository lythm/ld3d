struct LightResult
{
	float3							diffuse;
	float3							specular;
};
struct DirectionalLight
{
	float3	dir;
	float	intensity;
	float3	clr;
	float	specular_pow;
};
struct PointLight
{
	float3	clr;
	float	intensity;
	float	radius;
	float	specular_pow;
};

struct SpotLight
{
	float3	clr;
	float	intensity;
	float	range;
	float	cos_theta;
	float	specular_pow;
};

float rgb_2_il(float3 clr)
{
    return dot(clr, float3(0.2126f, 0.7152f, 0.0722f));
}

float dr_light_specular_il(float3 n, float3 l, float power)
{
	float3 v = float3(0, 0, -1);

	float3 r = reflect(-l, n);
	float s = saturate(dot(r, v));
	s = pow(s, power);

	return s;
}

LightResult dr_light_dir(float3 n, DirectionalLight light, float4x4 wv)
{
	float3 l = -mul(light.dir, (float3x3)wv);

	float il = saturate(dot(l, n)) * light.intensity;
	

	float s = dr_light_specular_il(n, l, light.specular_pow);

	s = s * light.intensity;
	
	LightResult ret;
	ret.diffuse		= il * light.clr;
	ret.specular	= s * light.clr;

	return ret;
}

LightResult dr_light_point(float3 p, float3 n, PointLight light, float4x4 wv)
{
	float3 center = mul(float4(0, 0, 0, 1), wv).xyz;
	
	float3 l = center - p;
	float d = length(l);
	l = normalize(l);

	float falloff = 1;
	float att = 1 - saturate(d * falloff / light.radius);

	float il = max(0, dot(l , n)) * light.intensity * att;

	float s = dr_light_specular_il(n, l, light.specular_pow);

	s = s * light.intensity * att;

	

	LightResult ret;
	ret.diffuse		= il * light.clr;
	ret.specular	= s * light.clr;

	return ret;
}


LightResult dr_light_spot(float3 p, float3 n, SpotLight light, float4x4 wv)
{
	float3 o = mul(float4(0,0,0,1), wv).xyz;
	float3 ld = mul(float4(0, 0, 1, 0), wv).xyz;

	float3 l = o - p;
	float d = length(l);
	l = normalize(l);
	
	float cos_angle = dot(ld, -l);
	
	float factor = step(light.cos_theta, cos_angle) * step(d , light.range / cos_angle);
	float il = max(0, dot(l , n)) * light.intensity * factor;
	
	float s = dr_light_specular_il(n, l, light.specular_pow);

	s = s * light.intensity * factor;


	LightResult ret;
	ret.diffuse		= il * light.clr;
	ret.specular	= s * light.clr;

	return ret;

}




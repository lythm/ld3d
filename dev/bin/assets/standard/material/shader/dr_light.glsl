#version 330

layout(row_major) uniform;

float g_specular_pow = 100;

struct LightResult
{
	vec3							diffuse;
	vec3							specular;
};
struct DirectionalLight
{
	vec3	dir;
	float	intensity;
	vec3	clr;
};
struct PointLight
{
	vec3	clr;
	float	intensity;
	float	radius;
};

struct SpotLight
{
	vec3	clr;
	float	intensity;
	float	range;
	float	cos_theta;
};

float saturate(float v)
{
	return clamp(v, 0.0, 1.0);
}

float rgb_2_il(vec3 clr)
{
    return dot(clr, vec3(0.2126f, 0.7152f, 0.0722f));
}

float dr_light_specular_il(vec3 n, vec3 l, float power)
{
	vec3 v = vec3(0, 0, -1);

	vec3 r = reflect(-l, n);
	float s = saturate(dot(r, v));
	s = pow(s, power);

	return s;
}

LightResult dr_light_dir(vec3 n, DirectionalLight light, mat4 wv)
{
	
	vec3 l = (-vec4(light.dir, 0) * wv).xyz;

	float il = saturate(dot(l, n) * light.intensity);
	
	float s = dr_light_specular_il(n, l, g_specular_pow);

	s = s * light.intensity;
	
	LightResult ret;
	ret.diffuse		= il * light.clr;
	//ret.specular	= s * light.clr;
	
	


	ret.specular = vec3(0, 0, 0);

	return ret;
}

LightResult dr_light_point(vec3 p, vec3 n, PointLight light, mat4 wv)
{
	vec3 center = (vec4(0, 0, 0, 1) * wv).xyz;
	
	vec3 l = center - p;
	float d = length(l);
	l = normalize(l);

	float falloff = 1;
	float att = 1 - saturate(d * falloff / light.radius);

	float il = max(0, dot(l , n)) * light.intensity * att;

	float s = dr_light_specular_il(n, l, g_specular_pow);

	s = s * light.intensity * att;

	

	LightResult ret;

	//ret.diffuse		= vec3(d / light.radius, d / light.radius, d / light.radius);
	ret.diffuse		= il * light.clr;
	ret.specular	= s * light.clr;

	return ret;
}


LightResult dr_light_spot(vec3 p, vec3 n, SpotLight light, mat4 wv)
{
	vec3 o = (vec4(0,0,0,1) * wv).xyz;
	vec3 ld = (vec4(0, 0, 1, 0) * wv).xyz;

	vec3 l = o - p;
	float d = length(l);
	l = normalize(l);
	
	float cos_angle = dot(ld, -l);
	
	float factor = step(light.cos_theta, cos_angle) * step(d , light.range / cos_angle);
	float il = max(0, dot(l , n)) * light.intensity;// * factor;
	
	float s = dr_light_specular_il(n, l, g_specular_pow);

	s = s * light.intensity * factor;


	LightResult ret;
	ret.diffuse		= il * light.clr;
	ret.specular	= s * light.clr * 0;

	return ret;

}





float fog_factor_linear(float start, float end, float coord)
{
	return 1.0 - clamp( (end-coord)/(end-start), 0.0, 1.0);
}
float fog_factor_exp(float density, float coord)
{
	return 1.0 - clamp(exp(-density*coord), 0.0, 1.0); 
}
float fog_factor_exp2(float density, float coord)
{
	return 1.0 - clamp(exp(-pow(density*coord, 2.0)), 0.0, 1.0);
}

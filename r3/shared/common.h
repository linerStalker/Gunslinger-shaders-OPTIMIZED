#ifndef SHARED_COMMON_H
#define SHARED_COMMON_H

cbuffer	dynamic_transforms
{
	uniform float4x4		m_WVP;
	uniform float3x4		m_WV;
	uniform float3x4	    m_W;
	
	uniform float4		L_material;
	uniform float4          hemi_cube_pos_faces;
	uniform float4          hemi_cube_neg_faces;
	uniform	float4 		dt_params;
}

cbuffer	shader_params
{
	float	m_AlphaRef;
}

cbuffer	static_globals
{
	uniform float3x4		m_V;
	uniform float4x4 	m_P;
	uniform float4x4 	m_VP;

	uniform float4		timers;

	uniform float4		fog_plane;
	uniform float4		fog_params;
	uniform float4		fog_color;

	uniform float4		L_ambient;
	uniform float3		L_sun_color;
	uniform float3		L_sun_dir_w;
	uniform float4		L_hemi_color;

	uniform float3 		eye_position;

	uniform float4 		pos_decompression_params;
	uniform float4 		pos_decompression_params2;
}

float 	calc_cyclic 	(float x)				
{
	float 	f=2.8284271f*frac(x)-1.4142136f;
	return 	f*f-1.f;
}

float2 	calc_xz_wave 	(float2 dir2D,float frac)		
{
	return  lerp	(float2(0.f,0.f),dir2D,frac);
}

#endif
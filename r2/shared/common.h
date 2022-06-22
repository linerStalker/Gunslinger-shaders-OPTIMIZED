#ifndef SHARED_COMMON_H
#define SHARED_COMMON_H

uniform half3x4	    m_W,m_WV,m_V;
uniform half4x4 	m_P,m_VP,m_WVP;
uniform float4x4 	m_texgen,mVPTexgen;
uniform half4		timers,L_hemi_color,L_ambient,fog_color;
uniform half3		L_sun_dir_w,L_sun_dir_e,eye_direction,eye_normal;
uniform float3 		eye_position,L_sun_color;
uniform	float4 		dt_params,fog_params;

half3 	unpack_bx2	(half3 v)	{return 2*v-1;}
float3 	unpack_bx4	(float3 v)	{return 4*v-2;} 

float2 	unpack_tc_base	(float2 xy,float du,float dv)
{
	return (xy+float2(du,dv))*(32.f/32768.f);
}

float2 	unpack_tc_lmap	(half2 tc)	{return tc*(1.f/32768.f);} 

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
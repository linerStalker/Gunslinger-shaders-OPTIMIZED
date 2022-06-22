#ifndef	COMMON_H
#define COMMON_H

#include "shared\common.h"

uniform half4		L_dynamic_props,L_dynamic_color,L_dynamic_pos;
uniform float4x4 	L_dynamic_xform,m_plmap_xform;
uniform float4 		m_plmap_clamp[2];

half  	calc_fogging 	(half4 w_pos)	{return dot(w_pos,fog_plane);}
half2 	calc_detail 	(half3 w_pos)
{
	float  	dtl=distance(w_pos,eye_position)*dt_params.w;
		dtl=min(dtl*dtl,1);
	half  	dt_mul=1-dtl;
	half  	dt_add=.5*dtl;
	return	half2	(dt_mul,dt_add);
}

float3 	calc_reflection	(float3 pos_w,float3 norm_w)
{
    return reflect(normalize(pos_w-eye_position),norm_w);
}

float4	calc_spot 	(out float4 tc_lmap,out float2 tc_att,float4 w_pos,float3 w_norm)	{
	float4 	s_pos=mul	(L_dynamic_xform,w_pos);
	tc_lmap=s_pos.xyww;
	tc_att=s_pos.z;
	float3 	L_dir_n=normalize	(w_pos-L_dynamic_pos.xyz);
	float 	L_scale=dot(w_norm,-L_dir_n);
	return 	L_dynamic_color*L_scale*saturate(calc_fogging(w_pos));
}

float4	calc_point 	(out float2 tc_att0,out float2 tc_att1,float4 w_pos,float3 w_norm)	{
	float3 	L_dir_n=normalize	(w_pos-L_dynamic_pos.xyz);
	float 	L_scale=dot		(w_norm,-L_dir_n);
	float3	L_tc=(w_pos-L_dynamic_pos.xyz)*L_dynamic_pos.w+.5f;
	tc_att0=L_tc.xz;
	tc_att1=L_tc.xy;
	return 	L_dynamic_color*L_scale*saturate(calc_fogging(w_pos));
}

float3	calc_sun		(float3 norm_w)	{return L_sun_color*max(dot((norm_w),-L_sun_dir_w),0);}
float3 	calc_model_hemi 	(float norm_y)	{return (norm_y*0.5+0.5)*L_dynamic_props.w*L_hemi_color;}
float3	calc_model_lq_lighting	(float3 norm_w){return calc_model_hemi(norm_w.y)+L_ambient+L_dynamic_props.xyz*calc_sun(norm_w);}
float3	_calc_model_lq_lighting	(float3 norm_w){return calc_model_hemi(norm_w.y)+L_ambient+.5*calc_sun(norm_w);}
float4 	calc_model_lmap 	(float3 pos_w)
{
	float3  pos_wc=clamp		(pos_w,m_plmap_clamp[0],m_plmap_clamp[1]);
	float4 	pos_w4c=float4	(pos_wc,1);
	float4 	plmap=mul		(m_plmap_xform,pos_w4c);
	return  plmap.xyww;
}

struct 	v_lmap
{
	float4 	P	:POSITION;
	float4	N	:NORMAL;
	float4 	T	:TANGENT;
	float4 	B	:BINORMAL;
	float2 	uv0	:TEXCOORD0;
	float2	uv1	:TEXCOORD1;
};
struct	v_vert
{
	float4 	P		:POSITION;
	float4	N		:NORMAL;
	float4 	T		:TANGENT;
	float4 	B		:BINORMAL;
	float4	color	:COLOR0;
	float2 	uv		:TEXCOORD0;
};
struct 	v_model
{
	float4 	pos	:POSITION;
	float3	norm	:NORMAL;
	float3	T	:TANGENT;
	float3	B	:BINORMAL;
#ifdef SKIN_COLOR
	float3 	rgb_tint;
#endif
	float2	tc	:TEXCOORD0;
};
struct	v_detail
{
	float4 	pos	:POSITION;
	int4 	misc	:TEXCOORD0;
};
struct 	vf_spot
{
	float4 hpos	:POSITION;
	float4 tc1	:TEXCOORD1;
	float4 color	:COLOR0;
	float2 tc2	:TEXCOORD2;
	float2 tc0	:TEXCOORD0;
};
struct 	vf_point
{
	float2 tc0	:TEXCOORD0;
	float2 tc1	:TEXCOORD1;
	float2 tc2	:TEXCOORD2;
	float4 hpos	:POSITION;
	float4 color	:COLOR0;
};

uniform sampler2D 	s_base,s_lmap,s_hemi,s_att,s_detail;
uniform samplerCUBE s_env;

#define def_distort	half(0.05f)

float3	v_hemi 		()		{return L_hemi_color;}
float3 	v_sun 		(float3 n)		{return L_sun_color*max(0,dot(n,-L_sun_dir_w));}
float3 	v_sun_wrap	(float3 n,float w)	{return L_sun_color*(w+(1-w)*dot(n,-L_sun_dir_w));}
half3	p_hemi		(float2 tc)
{
	half4	t_lmh=tex2D(s_hemi,tc);
	return  t_lmh.a;
}

#endif 
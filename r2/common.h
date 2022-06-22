#ifndef        COMMON_H
#define        COMMON_H

#include "shared\common.h"

#ifndef SMAP_size
#define SMAP_size        1024
#endif
#define PARALLAX_H 0.02
#define parallax float2(PARALLAX_H,-PARALLAX_H/2)

#ifdef    USE_R2_STATIC_SUN
#  define xmaterial half(1.0h/4.h)
#else
#  define xmaterial half(L_material.w)
#endif

uniform half4	hemi_cube_pos_faces,hemi_cube_neg_faces,L_material,Ldynamic_color,Ldynamic_pos,Ldynamic_dir,fog_plane;
uniform half4	J_direct[6],J_spot[6];

half          calc_fogging               (half4 w_pos){return dot(w_pos,fog_plane);}
half2         calc_detail                (half3 w_pos)
{
	float dtl  =distance(w_pos,eye_position)*dt_params.w;
	dtl =min(dtl*dtl,1);
	half dt_mul=1-dtl, dt_add=.5*dtl;
	return half2(dt_mul,dt_add);
}

float3         calc_reflection     (float3 pos_w,float3 norm_w)
{
    return reflect(normalize(pos_w-eye_position),norm_w);
}

float3        calc_sun_r1                (float3 norm_w){return L_sun_color*saturate(dot((norm_w),-L_sun_dir_w));}
float3        calc_model_hemi_r1         (float norm_y){return max(0,norm_y)*L_hemi_color;}
float3        calc_model_lq_lighting     (float3 norm_w){return L_material.x*calc_model_hemi_r1(norm_w.y)+L_ambient+L_material.y*calc_sun_r1(norm_w);}


struct v_static
{
	float4	P		:POSITION;
	float4	Nh		:NORMAL;
	float4	T		:TANGENT;
	float4	B		:BINORMAL;
	float4	color	:COLOR0;
	float2	tc		:TEXCOORD0;
	float2	lmh		:TEXCOORD1;
};

struct v_tree
{
	float4	P	:POSITION;
	float4	Nh	:NORMAL;
	float4	tc	:TEXCOORD0;
	float3	T	:TANGENT;
	float3	B	:BINORMAL;
};

struct v_model
{
	float4	P	:POSITION;       
	float3	N	:NORMAL;       
	float3	T	:TANGENT;       
	float3	B	:BINORMAL;       
	float2	tc	:TEXCOORD0;
};

struct v_detail
{
	float4	pos		:POSITION;       
	int4	misc	:TEXCOORD0;
};

#ifdef USE_HWSMAP
struct v_shadow_direct_aref
{
	float4	hpos:	POSITION;
	float2	tc0:	TEXCOORD1;
};
struct v_shadow_direct
{
	float4	hpos:	POSITION;
};
#else
struct v_shadow_direct_aref
{
	float4      hpos:       POSITION;
	float2      tc0:       TEXCOORD1;
	float       depth:        TEXCOORD0;
};
struct v_shadow_direct
{
	float4      hpos:       POSITION;
	float       depth:        TEXCOORD0;
};


#endif


struct p_bumped
{
	float4      position       :TEXCOORD1;
	float4      hpos       :POSITION;
#if defined(USE_R2_STATIC_SUN)&& !defined(USE_LM_HEMI)
	float4            tcdh       :TEXCOORD0;
#else
	float2            tcdh       :TEXCOORD0;
#endif
#ifdef USE_TDETAIL
	float2      tcdbump     	:TEXCOORD5;
    #ifdef USE_LM_HEMI
	float2      lmh            :TEXCOORD6;
    #endif
#else
    #ifdef USE_LM_HEMI
	float2      lmh            :TEXCOORD5;
    #endif
#endif
	half3       M1               :TEXCOORD2;
	half3       M2               :TEXCOORD3;
	half3       M3               :TEXCOORD4;
};

struct	p_flat
{
	float4                position       :TEXCOORD1;
	float4                 hpos       :POSITION;
#if defined(USE_R2_STATIC_SUN)&& !defined(USE_LM_HEMI)
    float4                    tcdh       :TEXCOORD0;
#else
    float2                    tcdh       :TEXCOORD0;
#endif
  #ifdef USE_TDETAIL
	float2                tcdbump               :TEXCOORD3;
    #ifdef USE_LM_HEMI
	float2         lmh     :TEXCOORD4;
    #endif
  #else
    #ifdef USE_LM_HEMI
	float2         lmh     :TEXCOORD3;
    #endif
  #endif
	half3                N               :TEXCOORD2;
};


struct f_deffer
{
	half4	position	:COLOR0;
	half4	Ne	:COLOR1;
	half4	C	:COLOR2;
};


uniform sampler	s_lmap, s_image;
uniform sampler2D	s_base,s_bump,s_detail,s_hemi,s_position,s_normal,s_accumulator,s_bloom,s_tonemap;
uniform sampler3D	s_material;


#define def_gloss       half(2.f /255.f)
#define def_aref        half(200.f/255.f)
#define def_virtualh    half(0.05f)
#define def_distort     half(0.05f)
#define def_hdr         half(9.h)


#define	LUMINANCE_VECTOR                 half3(0.3f,0.38f,0.22f)
void        tonemap              (out half4 low,out half4 high,half3 rgb,half scale)
{
        rgb=  	rgb*scale;

		const float fWhiteIntensity=1.7;

		const float fWhiteIntensitySQR=fWhiteIntensity*fWhiteIntensity;
#ifdef USE_BRANCHING		
        

		low=((rgb*(1+rgb/fWhiteIntensitySQR))/ (rgb+1)).xyzz;

        high=low/def_hdr;
#else
        low=   half4           (((rgb*(1+rgb/fWhiteIntensitySQR))/ (rgb+1)),       0);
        high=   half4       	(rgb/def_hdr,0);
#endif

}
half4 combine_bloom (half3  low,half4 high)
{
	return half4(low+high*high.a,1.h);
}

float3	v_hemi        	(float y)               	{return L_hemi_color*(.5f+.5f*y);}
float3	v_sun           (float3 n)               	{return L_sun_color*dot(n,-L_sun_dir_w);}
float3	v_sun_wrap      (float3 n,float w)       	{return L_sun_color*(w+(1-w)*dot(n,-L_sun_dir_w));}
half3   p_hemi          (float2 tc)
{
	half4 t_lmh =tex2D(s_hemi,tc);
	return t_lmh.a;
}


half Contrast(half Input,half ContrastPower)
{
	bool IsAboveHalf=Input>0.5;
	half ToRaise=saturate(2*(IsAboveHalf?1-Input:Input));
	half Output=0.5*pow(ToRaise,ContrastPower);
	Output=IsAboveHalf?1-Output:Output;
	return Output;
}

half get_noise(float2 co)
{
	return (frac(sin(dot(co.xy ,float2(12.9898,78.233)))*43758.5453))*0.5;
}

#define FXPS technique _render{pass _code{PixelShader=compile ps_3_0 main();}}
#define FXVS technique _render{pass _code{VertexShader=compile vs_3_0 main();}}

#endif
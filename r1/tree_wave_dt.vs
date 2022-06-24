#include "common.h"

struct av 
{
	float4 	pos	:POSITION;
	float4 	nc	:NORMAL;
	float4 	misc	:TEXCOORD0;
};

struct vf
{
	float4 HPOS	:POSITION;
	float2 tc0	:TEXCOORD0;
	float2 tc1	:TEXCOORD1;
	float4 c0	:COLOR0;
	float4 c1	:COLOR1;
	float  fog	:FOG;
};

uniform float3x4	m_xform;
uniform float4 		consts;
uniform float4 		wave;
uniform float4 		wind;
uniform float4		c_bias;
uniform float4		c_scale;
uniform float2 		c_sun;

vf main (av v)
{
	vf 		o;

	
	float3 	pos=mul	(m_xform,v.pos);

	
	float 	base=m_xform._24;
	float 	dp=calc_cyclic  (wave.w+dot(pos,(float3)wave));
	float 	H=pos.y-base;
	float 	frac=v.misc.z*consts.x;
	float 	inten=H*dp;
	float2 	result=calc_xz_wave	(wind.xz*inten,frac);
	float4 	f_pos=float4(pos.x+result.x,pos.y,pos.z+result.y,1);

	
	o.fog=calc_fogging 	(f_pos);

	
	o.HPOS=mul		(m_VP,f_pos);

	
	float3 	N=normalize 	(mul (m_xform,unpack_bx2(v.nc)));
	float 	L_base=v.nc.w;
	float4 	L_unpack=c_scale*L_base+c_bias;
	float3 	L_rgb=L_unpack.xyz;
	float3 	L_hemi=v_hemi()*L_unpack.w;

	float3 	L_sun=v_sun (N)*(L_base*c_sun.x+c_sun.y);
	float3 	L_final=L_rgb+L_hemi+L_sun+L_ambient;

	
	o.tc0.xy=(v.misc*consts).xy;
	o.tc1=o.tc0*dt_params;
	float2	dt=calc_detail		(f_pos);
	o.c0=float4 		(L_final,dt.x);
	o.c1=dt.y;

	return o;
}

#include "common.h"

struct av 
{
	float4 	pos	:POSITION;
	float4 	nc	:NORMAL;
	float4 	misc	:TEXCOORD0;
};

uniform float3x4	m_xform;
uniform float4 		consts;
uniform float4 		wave;
uniform float4 		wind;
uniform float4		c_bias;
uniform float4		c_scale;
uniform float2 		c_sun;

vf_spot main (av v)
{
	vf_spot		o;

	float3 	pos=mul	(m_xform,v.pos);

	float 	base=m_xform._24;
	float 	dp=calc_cyclic  (wave.w+dot(pos,(float3)wave));
	float 	H=pos.y-base;
	float 	frac=v.misc.z*consts.x;
	float 	inten=H*dp;
	float2 	result=calc_xz_wave	(wind.xz*inten,frac);
	float4 	f_pos=float4(pos,1);
	float3 	f_N=normalize 	(mul (m_xform,unpack_bx2(v.nc)));

	o.hpos=mul		(m_VP,f_pos);
	o.tc0=(v.misc*consts).xy;
	o.color=calc_spot 	(o.tc1,o.tc2,f_pos,f_N);

	return o;
}
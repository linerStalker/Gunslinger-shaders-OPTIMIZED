#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float4 C	:COLOR0;
	float2 tc	:TEXCOORD0;
};

uniform float4 		consts,wave,dir2D;
uniform float4 		array	[200]:register(c10);

vf main (v_detail v)
{
	vf 		o;

	int 	i=v.misc.w;
	float4  m1=array[i+1];
	float4 	pos;
 	pos.x=dot	(array[i],v.pos);
 	pos.y=dot	(m1,v.pos);
 	pos.z=dot	(array[i+2],v.pos);
	pos.w=1;

	float 	dp=calc_cyclic   (dot(pos,wave));
	float 	H=pos.y-m1.w;
	float 	frac=v.misc.z*consts.x;
	float2 	result=calc_xz_wave	(dir2D.xz*H*dp,frac);
	pos=float4(pos.x+result.x,pos.y,pos.z+result.y,1);
	o.hpos=mul	(m_WVP,pos);

	H=max(0.f,dp);
	o.C=array[i+3]*(consts.w+consts.z*H*frac);

	o.tc.xy=(v.misc*consts).xy;

	return o;
}
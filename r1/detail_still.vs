#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float4 C	:COLOR0;
	float2 tc	:TEXCOORD0;
};

uniform float4 		consts;
uniform float4 		array	[200]:register(c10);

vf main (v_detail v)
{
	vf 		o;

	int 	i=v.misc.w;

	float4 	pos;
 	pos.x=dot	(array[i],v.pos);
 	pos.y=dot	(array[i+1],v.pos);
 	pos.z=dot	(array[i+2],v.pos);
	pos.w=1;

	o.hpos=mul	(m_WVP,pos);
	o.C=array[i+3];
	o.tc.xy=(v.misc*consts).xy;

	return o;
}
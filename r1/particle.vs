#include "common.h"

struct vv
{
	float4 P	:POSITION;
	float2 tc	:TEXCOORD0;
	float4 c	:COLOR0;
};
struct vf
{
	float4 hpos	:POSITION;
	float2 tc	:TEXCOORD0;
	float4 c	:COLOR0;
	float  fog	:FOG;
};

vf main (vv v)
{
	vf 		o;

	o.hpos=mul	(m_WVP,v.P);
	o.tc=v.tc;
	o.c=v.c;
	o.fog=calc_fogging (v.P);

	return o;
}

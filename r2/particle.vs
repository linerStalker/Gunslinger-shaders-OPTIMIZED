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


#ifdef USE_SOFT_PARTICLES
	float4 tctexgen	:TEXCOORD1;
#endif	
};

vf main (vv v)
{
	vf 		o;

	o.hpos=mul	(m_WVP,v.P);

	o.tc=v.tc;
	o.c=v.c;


#ifdef USE_SOFT_PARTICLES
	o.tctexgen=mul(mVPTexgen,v.P);
	o.tctexgen.z=o.hpos.z;
#endif	

	return o;
}

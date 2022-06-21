#include "common.h"
#include "shared\wmark.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float3 c0	:COLOR0;//c0=all lighting
	float  fog	:FOG;
};

vf main (v_static v)
{
	vf 		o;

	float3 	N=unpack_bx2	(v.Nh);
	float4 	P=wmark_shift	(v.P,N);
	o.hpos=mul		(m_VP,P);//xform,input in world coords
	o.tc0=unpack_tc_base	(v.tc.xy,v.T.w,v.B.w);//copy tc

	o.c0=0;//L_final;
	o.fog=saturate(calc_fogging 		(v.P));//fog,input in world coords

	return o;
}

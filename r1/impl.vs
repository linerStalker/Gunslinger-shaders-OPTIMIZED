#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float2 tc1	:TEXCOORD1;
	float3 c0	:COLOR0;
	float3 c1	:COLOR1;
	float  fog	:FOG;
};

vf main (v_lmap v)
{
	vf 		o;

	float3 	N=unpack_bx2		(v.N);
	o.hpos=mul			(m_VP,v.P);
	o.tc0=unpack_tc_base	(v.uv0.xy,v.T.w,v.B.w);
	o.tc1=o.tc0;
	o.c0=v_hemi();
	o.c1=v_sun			(N);
	o.fog=calc_fogging 		(v.P);

	return o;
}
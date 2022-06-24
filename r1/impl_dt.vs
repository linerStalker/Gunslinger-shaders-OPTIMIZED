#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float2 tc1	:TEXCOORD1;
	float2 tc2	:TEXCOORD2;
	float4 c0	:COLOR0;
	float4 c1	:COLOR1;
	float  fog	:FOG;
};

vf main (v_lmap v)
{
	vf 		o;

	float2 	dt=calc_detail		(v.P);
	float3	N=unpack_bx2		(v.N);
	o.hpos=mul			(m_VP,v.P);
	o.tc0=unpack_tc_base	(v.uv0.xy,v.T.w,v.B.w);
	o.tc1=o.tc0;
	o.tc2=o.tc0*dt_params;
	o.c0=float4 		(v_hemi(),dt.x);
	o.c1=float4 		(v_sun(N),dt.y);
	o.fog=calc_fogging 		(v.P);

	return o;
}

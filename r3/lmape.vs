
#define	USE_LM_HEMI
#include "common.h"

struct 	v_lmap
{
	float4 	pos		:POSITION;
	float4	norm	:NORMAL;
	float2 	tc0		:TEXCOORD0;
	float2	tc1		:TEXCOORD1;
};
struct vf
{
	float2 tc0	:TEXCOORD0;
	float2 tc1	:TEXCOORD1;
	float2 tch	:TEXCOORD2;
	float3 tc2	:TEXCOORD3;
	float3 c0	:COLOR0;
	float3 c1	:COLOR1;
	float  fog	:FOG;
	float4 hpos	:SV_Position;
};

vf main(v_static v)
{
	vf 		o;
	
	o.hpos=mul				(m_VP,v.P);
	o.tc0=unpack_tc_base	(v.tc.xy,v.T.w,v.B.w);
	o.tc1=unpack_tc_lmap	(v.lmh);
	o.tch=o.tc1;
	float3 	norm_w=normalize(unpack_bx2(v.Nh));
	o.tc2=calc_reflection	(float3(v.P),norm_w);
	o.c0=v_hemi(norm_w.y);
	o.c1=v_sun	(norm_w);
	o.fog.x=saturate(calc_fogging (v.P));

	return o;
}

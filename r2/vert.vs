#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float4 c0	:COLOR0;
	float  fog	:FOG;
};

vf main_vs_2_0 (v_static v)
{
	vf 		o;

	float3 	N=unpack_bx2		(v.Nh);
	o.hpos=mul				(m_VP,v.P);
	o.tc0=unpack_tc_base	(v.tc.xy,v.T.w,v.B.w);

	float3 	L_rgb=v.color.xyz;
	float3 	L_hemi=v_hemi(N.y)*v.Nh.w;
	float3 	L_sun=v_sun(N)*v.color.w;
	float3 	L_final=L_rgb+L_hemi+L_sun+L_ambient;

	o.fog=saturate(calc_fogging 		(v.P));
	o.c0=half4(L_final,o.fog);

	return o;
}
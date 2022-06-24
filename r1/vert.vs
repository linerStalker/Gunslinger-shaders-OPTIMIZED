#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float3 c0	:COLOR0;
	float  fog	:FOG;
};

vf main (v_vert v)
{
	vf 		o;

	float3 	N=unpack_bx2		(v.N);
	o.hpos=mul			(m_VP,v.P);
	o.tc0=unpack_tc_base	(v.uv.xy,v.T.w,v.B.w);

	float3 	L_rgb=v.color.xyz;
	float3 	L_hemi=v_hemi()*v.N.w;
	float3 	L_sun=v_sun(N)*v.color.w;
	float3 	L_final=L_rgb+L_hemi+L_sun+L_ambient;

	o.c0=L_final;
	o.fog=calc_fogging 		(v.P);

	return o;
}

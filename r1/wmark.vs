#include "common.h"
#include "shared\wmark.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float4 c0	:COLOR0;
	float  fog	:FOG;
};

vf main (v_vert v)
{
	vf 		o;

	float3 	N=unpack_bx2	(v.N);
	float4 	P=wmark_shift		(v.P,N.xyz);
	o.hpos=mul				(m_VP,P);
	o.tc0=unpack_tc_base	(v.uv.xy,v.T.w,v.B.w);

	float3 		L_rgb=v.color.xyz;
	float3 		L_hemi=v_hemi()*v.N.w;
	float3 		L_sun=v_sun(N)*v.color.w;
	float3 		L_final=L_rgb+L_hemi+L_sun+L_ambient;

	o.c0.rgb=L_final;
	o.c0.a=calc_fogging 		(P);
	o.fog=1;

	return o;
}
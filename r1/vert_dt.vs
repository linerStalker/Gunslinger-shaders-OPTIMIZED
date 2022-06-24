#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float2 tc1	:TEXCOORD1;
	float4 c0	:COLOR0;
	float4 c1	:COLOR1;
	float  fog	:FOG;
};

vf main (v_vert v)
{
	vf 		o;

	float3 	N=unpack_bx2		(v.N);
	o.hpos=mul			(m_VP,v.P);
	o.tc0=unpack_tc_base	(v.uv.xy,v.T.w,v.B.w);
	o.tc1=o.tc0*dt_params;

	float3 	L_rgb=v.color.xyz;
	float3 	L_hemi=v_hemi()*v.N.w;
	float3 	L_sun=v_sun(N)*v.color.w;
	float3 	L_final=L_rgb+L_hemi+L_sun+L_ambient;

	float2	dt=calc_detail		(v.P);

	o.c0=float4(L_final.x,L_final.y,L_final.z,dt.x);
	o.c1=dt.y;
	o.fog=calc_fogging 		(v.P);

	return o;
}

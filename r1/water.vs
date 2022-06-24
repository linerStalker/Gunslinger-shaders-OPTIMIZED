#include "common.h"
#include "shared\waterconfig.h"
#include "shared\watermove.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tbase	:TEXCOORD0;
	float3 tenv	:TEXCOORD1;
	float4 c0	:COLOR0;
	float  fog	:FOG;
};

vf main (v_vert v)
{
	vf 		o;

	float4 	P=v.P;
	float3 	N=unpack_bx2	(v.N);
		
		P=watermove	(P);

	float2 	tc_base=unpack_tc_base	(v.uv.xy,v.T.w,v.B.w);

	float 	amount;
	float3 	tc_refl=waterrefl 		(amount,P,N);

	o.tbase=tc_base;
	o.tenv=tc_refl;

	float3 	L_rgb=v.color.xyz;
	float3 	L_hemi=v_hemi()*v.N.w;
	float3 	L_sun=v_sun(N)*v.color.w;
	float3 	L_final=L_rgb+L_hemi+L_sun+L_ambient;

	o.hpos=mul			(m_VP,P);
	o.c0=float4		(L_final,amount);
	o.fog=calc_fogging 		(P);

	return o;
}

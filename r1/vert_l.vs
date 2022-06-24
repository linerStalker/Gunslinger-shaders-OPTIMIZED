#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float4 c0	:COLOR0;
};

vf main (v_vert v)
{
	vf 		o;

	float3 	N=unpack_bx2		(v.N);
	float3 	L_rgb=v.color.xyz;
	float3 	L_hemi=v_hemi()*v.N.w;
	float 	L_sun=v.color.w;
	float3 	L_final=L_rgb+L_hemi+L_ambient;

	o.hpos=mul			(m_VP,v.P);
	o.c0=float4 		(L_final.x,L_final.y,L_final.z,L_sun);
	return o;
}

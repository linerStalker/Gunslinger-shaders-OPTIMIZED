#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float4 c0	:COLOR0;
};

vf main (v_vert v)
{
	vf 		o;

	o.hpos=mul			(m_WVP,v.P);
	o.tc0=unpack_tc_base	(v.uv.xy,v.T.w,v.B.w);

	float3  dir_v=normalize		(mul(m_WV,v.P));
	float3 	norm_v=normalize 		(mul(m_WV,unpack_bx2(v.N)));
	float 	fade=abs			(dot(dir_v,norm_v));
	o.c0=fade;

	return o;
}
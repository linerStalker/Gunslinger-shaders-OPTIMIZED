#include "common.h"
#include "shared\wmark.h"

vf_point main (v_vert v)
{
	vf_point		o;

	float3 	N=unpack_bx2	(v.N);
	float4 	P=wmark_shift	(v.P,N.xyz);
	o.hpos=mul				(m_VP,P);
	o.tc0=unpack_tc_base	(v.uv.xy,v.T.w,v.B.w);
	o.color=calc_point 		(o.tc1,o.tc2,P,N);

	return o;
}

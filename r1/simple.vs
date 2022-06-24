#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float  fog	:FOG;
};

vf main (v_vert v)
{
	vf 		o;

	o.hpos=mul			(m_VP,v.P);
	o.tc0=unpack_tc_base	(v.uv.xy,v.T.w,v.B.w);
	o.fog=calc_fogging 		(v.P);

	return o;
}

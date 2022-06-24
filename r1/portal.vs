#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float4 c	:COLOR0;
	float  fog	:FOG;
};

vf main (v_vert v)
{
	vf 		o;

	o.hpos=mul			(m_VP,v.P);
	o.c=v.color;
	o.fog=calc_fogging 		(v.P);

	return o;
}

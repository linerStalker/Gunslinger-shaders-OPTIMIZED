#include "common.h"

struct	v_vert
{
	float4 	pos	:POSITION;
	float4	color	:COLOR0;
};
struct 	vf
{
	float4 hpos	:POSITION;
	float4 c	:COLOR0;
	float  fog	:FOG;
};

vf main (v_vert v)
{
	vf 		o;

	o.hpos=mul(m_VP,v.pos);
	o.c=v.color;
	o.fog=calc_fogging(v.pos);
	o.fog=saturate(o.fog);
	o.c.rgb=lerp(fog_color,o.c,o.fog);
	o.c.a=o.fog;

#ifdef USE_VTF
	float scale=tex2Dlod	(s_tonemap,float4(.5,.5,.5,.5)).x;
	o.c.rgb=o.c.rgb*scale;
#endif	

	return o;
	
}

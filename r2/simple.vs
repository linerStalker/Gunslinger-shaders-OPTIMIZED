#include "common.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
};

vf main (v_model v)
{
	vf 		o;

	o.hpos=mul	(m_WVP,v.P);
	o.tc0=v.tc;

	return o;
}

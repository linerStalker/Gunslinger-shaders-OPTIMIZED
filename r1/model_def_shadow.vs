#include "common.h"
#include "skin.h"

struct vf
{
	float4	hpos	:POSITION;
	float4 	c0	:COLOR0;
};

vf 	_main 	(v_model v)
{
	vf 		o;

	o.hpos=mul	(m_WVP,v.pos);
	o.c0=0;
	return o;
}


#define SKIN_LQ
#define SKIN_VF vf
#include "skin_main.h"
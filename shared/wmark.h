#ifndef  WMARK_H
#define  WMARK_H
#include "common.h"

float4 	wmark_shift 	(float3 P,float3 xyz)
{
	float3	sd=eye_position-P;
	float 	d=length(sd);
	float 	s=lerp(0.003f,0.011f,d);
	P+=xyz*0.007f;
	P-=normalize(eye_direction+normalize(P-eye_position))*s;
	return	float4	(P,1.f);
}
#endif
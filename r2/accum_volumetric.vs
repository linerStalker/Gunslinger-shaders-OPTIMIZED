#include "common.h"

float3	vMinBounds;
float3	vMaxBounds;

struct vf
{
	float4 	hpos		:POSITION;
	float3 	lightToPos	:TEXCOORD0;
	float3 	vPos		:TEXCOORD1;
	half 	fDensity	:TEXCOORD2;

};

vf main (v_static v)
{
	vf 		o;
	float4	vPos;
	vPos.xyz=lerp(vMinBounds,vMaxBounds,v.P);
	vPos.w=1;
	o.hpos=mul			(m_P,vPos);

	o.lightToPos=vPos.xyz-Ldynamic_pos.xyz;
	o.vPos=vPos;



	o.fDensity=1.0h/40.0h;


	return o;
}

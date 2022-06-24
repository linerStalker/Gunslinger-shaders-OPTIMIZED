#include "common.h"

struct 	_in        	{
	float4 	p	:POSITION;
	float2	tcJ	:TEXCOORD0;
};

struct 	_out        	{
	float4 	hpos	:POSITION;
#ifdef USE_VTF
  	float4 	tc0	:TEXCOORD0;
#else
  	float2 	tc0	:TEXCOORD0;
#endif
	float2	tcJ	:TEXCOORD1;
};


_out 	main	(_in   I)
{
	_out 		O;
	O.hpos=float4	(I.p.x,-I.p.y,0,1);
#ifdef USE_VTF
	float  	scale=tex2Dlod 	(s_tonemap,float4(.5,.5,.5,.5)).x;
	O.tc0=float4	(I.p.zw,scale,scale);
#else
	O.tc0=I.p.zw;
#endif

	O.tcJ=I.tcJ;

 	return	O;
}

FXVS;

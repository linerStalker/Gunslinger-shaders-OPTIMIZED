#include "common.h"

uniform float3x4		m_xform;
uniform float3x4		m_xform_v;
uniform float4 			consts;
uniform float4 			c_scale,c_bias,wind,wave;



v_shadow_direct_aref 	main	(v_tree  	I)
{
	v_shadow_direct_aref 	O;

	
	float3 	pos=mul		(m_xform ,I.P);

	
	float 	base=m_xform._24;
	float 	dp=calc_cyclic  (wave.w+dot(pos,(float3)wave));
	float 	H=pos.y-base;
	float 	frac=I.tc.z*consts.x;
	float 	inten=H*dp;
	float2 	result=calc_xz_wave	(wind.xz*inten,frac);
#ifdef USE_TREEWAVE
			result=0;
#endif
	float4 	f_pos=float4(pos.x+result.x,pos.y,pos.z+result.y,1);

	O.hpos=mul		(m_VP,f_pos);
	O.tc0=(I.tc*consts).xy;
#ifndef USE_HWSMAP
	O.depth=O.hpos.z;
#endif
 	return	O;
}
FXVS;

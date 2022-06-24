#include "common.h"
#include "skin.h"

struct vf
{
	float4 hpos	:POSITION;
	float2 tc0	:TEXCOORD0;
	float4 c0	:COLOR0;
};

vf 	_main (v_model v)
{
	vf 		o;

	o.hpos=mul			(m_WVP,v.P);
	o.tc0=v.tc.xy;

	
	float3  dir_v=normalize    (mul(m_WV,v.P));
	float3  norm_v=normalize    (mul(m_WV,v.N));
	float 	fade=abs			(dot(dir_v,norm_v));
	o.c0=fade;

	return o;
}


#ifdef 	SKIN_NONE
vf	main(v_model v)		{return _main(v);}
#endif

#ifdef 	SKIN_0
vf	main(v_model_skinned_0 v)	{return _main(skinning_0(v));}
#endif

#ifdef SKIN_1
vf	main(v_model_skinned_1 v)	{return _main(skinning_1(v));}
#endif

#ifdef SKIN_2
vf	main(v_model_skinned_2 v)	{return _main(skinning_2(v));}
#endif

#ifdef SKIN_3
vf	main(v_model_skinned_3 v)	{return _main(skinning_3(v));}
#endif

#ifdef SKIN_4
vf	main(v_model_skinned_4 v)	{return _main(skinning_4(v));}
#endif
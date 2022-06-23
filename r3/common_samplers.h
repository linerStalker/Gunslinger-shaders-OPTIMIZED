#ifndef	common_samplers_h_included
#define	common_samplers_h_included

sampler smp_nofilter,smp_rtlinear,smp_linear,smp_base,smp_material;

#ifdef USE_MSAA
Texture2D	s_base,s_bump,s_detail,s_hemi,s_lmap,s_bloom,s_image,s_tonemap;
TEXTURE2DMS(float4,MSAA_SAMPLES)	s_generic,s_position,s_normal,s_diffuse,s_accumulator;
#else
Texture2D   s_base,s_bump,s_detail,s_hemi,s_lmap,s_bloom,s_image,s_tonemap,s_generic,s_position,s_normal,s_diffuse,s_accumulator;
#endif
Texture3D	s_material;

#endif	
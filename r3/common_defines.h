#ifndef	common_defines_h_included
#define	common_defines_h_included


#define GBUFFER_OPTIMIZATION
#define USE_SUNMASK
#define MSAA_OPTIMIZATION
#define USE_HWSMAP

#define def_gloss       float(2.f /255.f)
#define def_aref        float(200.f/255.f)
#define def_virtualh    float(0.05f)
#define def_distort     float(0.05f)
#define def_hdr         float(9.h)

#define	LUMINANCE_VECTOR	float3(0.3f,0.38f,0.22f)

#if defined(SM_5) || defined(SM_4_1)
    #define TEXTURE2DMS(a, b) Texture2DMS<a>
#else
    #define TEXTURE2DMS(a, b) Texture2DMS<a, b>
#endif


#ifndef SMAP_size
#define SMAP_size        2048
#endif
#define PARALLAX_H 0.02
#define parallax float2(PARALLAX_H,-PARALLAX_H/2)


#endif	
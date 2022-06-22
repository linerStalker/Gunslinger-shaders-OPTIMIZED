#ifndef	common_defines_h_included
#define	common_defines_h_included



#define def_gloss       float(2.f /255.f)
#define def_aref        float(200.f/255.f)
#define def_virtualh    float(0.05f)
#define def_distort     float(0.05f)
#define def_hdr         float(9.h)

#define	LUMINANCE_VECTOR	float3(0.3f,0.38f,0.22f)


#ifndef SMAP_size
#define SMAP_size        1024
#endif
#define PARALLAX_H 0.02
#define parallax float2(PARALLAX_H,-PARALLAX_H/2)


#endif	
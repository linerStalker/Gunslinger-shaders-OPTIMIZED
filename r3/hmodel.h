#ifndef        HMODEL_H
#define HMODEL_H

#include "common.h"

TextureCube		env_s0, env_s1;

uniform float4	env_color;//color.w=lerp factor
uniform float3x4	m_v2w;

void hmodel
(
	out float3 hdiffuse,out float3 hspecular,
	float m,float h,float s,float3 Pnt,float3 normal
)
{
	//reflection vector
	float3	nw=mul(m_v2w,normal), v2PntL=normalize(Pnt), v2Pnt=mul(m_v2w,v2PntL), vreflect=reflect(v2Pnt,nw);
	float	hspec=.5h+.5h*dot(vreflect,v2Pnt);
#ifdef USE_GAMMA_22
	float4	light=s_material.SampleLevel(smp_material,float3(h*h,hspec,m),0).xxxy;
#else
	float4	light=s_material.SampleLevel(smp_material,float3(h,hspec,m),0).xxxy;
#endif

	float3	e0d=env_s0.SampleLevel(smp_rtlinear,nw,0), e1d=env_s1.SampleLevel(smp_rtlinear,nw,0), env_d=env_color.xyz*lerp(e0d,e1d,env_color.w);
	env_d*=env_d;//contrast
	hdiffuse=env_d*light.xyz+L_ambient.rgb;

	//specular color
	vreflect.y=vreflect.y*2-1;//fake remapping
	float3	e0s=env_s0.SampleLevel(smp_rtlinear,vreflect,0), e1s=env_s1.SampleLevel(smp_rtlinear,vreflect,0);
	float3	env_s=env_color.xyz*lerp(e0s,e1s,env_color.w);
			env_s*=env_s;//contrast
		hspecular=env_s*light.w*s;
}
#endif
#ifndef        HMODEL_H
#define HMODEL_H

#include "common.h"

TextureCube		env_s0, env_s1;

uniform float4	env_color;
uniform float3x4	m_v2w;

void hmodel
(
	out float3 hdiffuse,out float3 hspecular,
	float m,float h,float s,float3 Pnt,float3 normal
)
{
	
	float3	nw=mul(m_v2w,normal), v2PntL=normalize(Pnt), v2Pnt=mul(m_v2w,v2PntL), vreflect=reflect(v2Pnt,nw);
	float	hspec=.5h+.5h*dot(vreflect,v2Pnt);
	float4	light=s_material.SampleLevel(smp_material,float3(h,hspec,m),0).xxxy;

	float3	e0d=env_s0.SampleLevel(smp_rtlinear,nw,0), e1d=env_s1.SampleLevel(smp_rtlinear,nw,0), env_d=env_color.xyz*lerp(e0d,e1d,env_color.w);
	env_d*=env_d;
	hdiffuse=env_d*light.xyz+L_ambient.rgb;

	
	vreflect.y=vreflect.y*2-1;
	float3	e0s=env_s0.SampleLevel(smp_rtlinear,vreflect,0), e1s=env_s1.SampleLevel(smp_rtlinear,vreflect,0);
	float3	env_s=env_color.xyz*lerp(e0s,e1s,env_color.w);
			env_s*=env_s;
		hspecular=env_s*light.w*s;
}
#endif
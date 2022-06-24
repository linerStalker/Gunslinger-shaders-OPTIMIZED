#ifndef        HMODEL_H
#define HMODEL_H

#include "common.h"

uniform samplerCUBE         env_s0, env_s1;
uniform half4               env_color;
uniform half3x4             m_v2w;

void        hmodel                 (out half3 hdiffuse,out half3 hspecular,half m,half h,half s,float3 point,half3 normal)
{
        half3         nw=mul                 (m_v2w,normal);
        
        float3        v2pointL=normalize        (point);
        half3 v2point=mul(m_v2w,v2pointL), vreflect=reflect(v2point,nw);
        half hspec=.5h+.5h*dot(vreflect,v2point);

		half4 light =tex3D(s_material,half3(h,hspec,m)); 

        
        half3         e0d=texCUBE(env_s0,nw), e1d=texCUBE(env_s1,nw);
        half3         env_d=env_color.xyz*lerp(e0d,e1d,env_color.w);
					env_d*=env_d;
        hdiffuse       =env_d*light.xyz+L_ambient.rgb;

        
        vreflect.y=vreflect.y*2-1;
		
        e0d=texCUBE(env_s0,vreflect), e1d=texCUBE(env_s1,vreflect), env_d=env_color.xyz*lerp(e0d,e1d,env_color.w);
		env_d*=env_d;
        hspecular=env_d*light.w*s;
}

void         hmodel_table        (out half3 hdiffuse,out half3 hspecular,half m,half h,half s,half3 point,half3 normal)
{

        
        half3 v2point =normalize(point), vreflect=reflect(v2point,normal);
        half hspec =.5h+.5h*dot(vreflect,v2point);

        
        half4 light  =tex3D(s_material,half3(h,hspec,m));       

        
        half3 ED=texCUBE(env_s0,normal), ES=texCUBE(env_s0,vreflect);

        hdiffuse  =ED*light.xyz+L_ambient.rgb;
        hspecular  =ES*light.w*s;
}

#endif
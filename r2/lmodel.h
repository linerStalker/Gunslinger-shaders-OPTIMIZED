#ifndef	LMODEL_H
#define LMODEL_H

#include "common.h"



half4 	plight_infinity		(half m,half3 point,half3 normal,half3 light_direction)
{
  half3 N=normal;
  half3 V=-normalize	(point);
  half3 L=-light_direction;
  half3 H=normalize	(L+V);
  return tex3D 		(s_material,half3(dot(L,N),dot(H,N),m));
}
half4 	plight_infinity2	(half m,half3 point,half3 normal,half3 light_direction)
{
  	half3 N=normal;
  	half3 V=-normalize		(point);
  	half3 L=-light_direction;
 	half3 H=normalize			(L+V);
	half3 R=reflect         	(-V,N);
	half 	s=saturate(dot(L,R));
			s=saturate(dot(H,N));
	half 	f=saturate(dot(-V,R));
			s*=f;
	half4	r=tex3D 			(s_material,half3(dot(L,N),s,m));
			r.w=pow(saturate(s),4);
  	return	r;
}
half4 	plight_local		(half m,half3 point,half3 normal,half3 light_position,half light_range_rsq,out float rsqr){
  half3 N=normal;
  half3 L2P=point-light_position;                		
  half3 V=-normalize	(point);
  half3 L=-normalize	((half3)L2P);
  half3 H=normalize	(L+V);
		rsqr=dot		(L2P,L2P);
  half  att=saturate	(1-rsqr*light_range_rsq);
  half4 light=tex3D		(s_material,half3(dot(L,N),dot(H,N),m));
  return att*light;
}

half4	blendp	(half4	value,float4 	tcp)
{
	return 	value;
}
half4	blend	(half4	value,float2 	tc)
{
	return 	value;
}
#endif
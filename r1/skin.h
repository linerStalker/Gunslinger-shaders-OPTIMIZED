#ifndef	SKIN_H
#define SKIN_H

#include "common.h"

struct 	v_model_skinned_0
{
	float4 	P	:POSITION;
	float3	N	:NORMAL;
	float3	T	:TANGENT;
	float3	B	:BINORMAL;
	float2	tc	:TEXCOORD0;
};
struct 	v_model_skinned_1
{
	float4 	P	:POSITION;
	int4	N	:NORMAL;
	float3	T	:TANGENT;
	float3	B	:BINORMAL;
	float2	tc	:TEXCOORD0;
};
struct 	v_model_skinned_2
{
	float4 	P	:POSITION;
	float4 	N	:NORMAL;
	float3	T	:TANGENT;
	float3	B	:BINORMAL;
	int4 	tc	:TEXCOORD0;
};

struct 	v_model_skinned_3
{
	float4 	P	:POSITION;
	float4 	N	:NORMAL;
	float4	T	:TANGENT;
	float4	B	:BINORMAL;
	int4 	tc	:TEXCOORD0;
};

struct 	v_model_skinned_4
{
	float4 	P	:POSITION;
	float4 	N	:NORMAL;
	float4	T	:TANGENT;
	float4	B	:BINORMAL;
	int2 	tc	:TEXCOORD0;
	float4 	ind:TEXCOORD1;
};

float4 	u_position	(float3 xyz)	{return float4(xyz*(12.f/32768.f),1.f);}

uniform float4 	sbones_array	[230]:register(vs,c22);
float3 	skinning_dir 	(float3 dir,float3 m0,float3 m1,float3 m2)
{
	float3 	U=unpack_bx2(dir);
	return 	float3	
		(
			dot	(m0,U),
			dot	(m1,U),
			dot	(m2,U)
);
}
float4 	skinning_pos 	(float3 xyz,float4 m0,float4 m1,float4 m2)
{
	float4 	P=u_position	(xyz);
	return 	float4
		(
			dot	(m0,P),
			dot	(m1,P),
			dot	(m2,P),
			1
);
}

v_model skinning_0	(v_model_skinned_0	v)
{
	v_model 	o;
	o.pos=u_position(v.P.xyz);
	o.norm=unpack_bx2(v.N);
	o.T=unpack_bx2(v.T);
	o.B=unpack_bx2(v.B);
	o.tc=v.tc		*(16.f/32768.f);
#ifdef SKIN_COLOR
	o.rgb_tint=float3	(0,0,2);
#endif
	return o;
}
v_model skinning_1 	(v_model_skinned_1	v)
{
	int 	mid=v.N.w*(int)255;
	float4  m0=sbones_array[mid];
	float4  m1=sbones_array[mid+1];
	float4  m2=sbones_array[mid+2];

	v_model 	o;
	o.pos=skinning_pos(v.P.xyz,m0,m1,m2);
	o.norm=skinning_dir(v.N,m0,m1,m2);
	o.T=skinning_dir(v.T,m0,m1,m2);
	o.B=skinning_dir(v.B,m0,m1,m2);
	o.tc=v.tc		*(16.f/32768.f);
#ifdef SKIN_COLOR
	o.rgb_tint=float3	(0,2,0);
#endif
	return o;
}
v_model skinning_2 	(v_model_skinned_2	v)
{
	#ifdef SKIN_COLOR
		int 	id_0=v.tc.z;
		float4  m0_0=sbones_array[id_0];
		float4  m1_0=sbones_array[id_0+1];
		float4  m2_0=sbones_array[id_0+2];
		int 	id_1=v.tc.w;
		float4  m0_1=sbones_array[id_1];
		float4  m1_1=sbones_array[id_1+1];
		float4  m2_1=sbones_array[id_1+2];
	#else
		int 	id=v.tc.z;
		float4  m0_0=sbones_array[id];
		float4  m1_0=sbones_array[id+1];
		float4  m2_0=sbones_array[id+2];
		id=v.tc.w;
		float4  m0_1=sbones_array[id];
		float4  m1_1=sbones_array[id+1];
		float4  m2_1=sbones_array[id+2];
	#endif

	float 	w=v.N.w;
	float4  m0=lerp(m0_0,m0_1,w);
	float4  m1=lerp(m1_0,m1_1,w);
	float4  m2=lerp(m2_0,m2_1,w);

	v_model 	o;
	o.pos=skinning_pos(v.P.xyz,m0,m1,m2);
	o.norm=skinning_dir(v.N,m0,m1,m2);
	o.T=skinning_dir(v.T,m0,m1,m2);
	o.B=skinning_dir(v.B,m0,m1,m2);
	o.tc=v.tc		*(16.f/32768.f);
#ifdef SKIN_COLOR
	o.rgb_tint=float3	(2,0,0);
	if (id_0==id_1)	o.rgb_tint=float3(1,2,0);
#endif
	return o;
}

v_model skinning_2lq 	(v_model_skinned_2	v)
{
	int 	id=v.tc.z;
	float4  m0=sbones_array[id];
	float4  m1=sbones_array[id+1];
	float4  m2=sbones_array[id+2];

	v_model 	o;
	o.pos=skinning_pos	(v.P.xyz,m0,m1,m2);
	o.norm=skinning_dir	(v.N,m0,m1,m2);
	o.T=skinning_dir	(v.T,m0,m1,m2);
	o.B=skinning_dir	(v.B,m0,m1,m2);
	o.tc=v.tc		*(16.f/32768.f);
#ifdef SKIN_COLOR
	o.rgb_tint=float3	(0,2,0);
#endif
	return o;
}

v_model skinning_3 	(v_model_skinned_3	v)
{
	#ifdef SKIN_COLOR
		int 	id_0=v.tc.z;
		float4  m0=sbones_array[id_0];
		float4  m1=sbones_array[id_0+1];
		float4  m2=sbones_array[id_0+2];
		int 	id_1=v.tc.w;
		float4  m0_1=sbones_array[id_1];
		float4  m1_1=sbones_array[id_1+1];
		float4  m2_1=sbones_array[id_1+2];
		int 	id_2=v.B.w*255+0.3;
		float4  m0_2=sbones_array[id_2];
		float4  m1_2=sbones_array[id_2+1];
		float4  m2_2=sbones_array[id_2+2];
	#else
		int 	id=v.tc.z;
		float4  m0=sbones_array[id];
		float4  m1=sbones_array[id+1];
		float4  m2=sbones_array[id+2];
		id=v.tc.w;
		float4  m0_1=sbones_array[id];
		float4  m1_1=sbones_array[id+1];
		float4  m2_1=sbones_array[id+2];
		id=v.B.w*255+0.3;
		float4  m0_2=sbones_array[id];
		float4  m1_2=sbones_array[id+1];
		float4  m2_2=sbones_array[id+2];
	#endif

	float 	w0=v.N.w,w1=v.T.w,w2=1.0-w0-w1;
	m0*=w0;
	m1*=w0;
	m2*=w0;

	m0+=m0_1*w1;
	m1+=m1_1*w1;
	m2+=m2_1*w1;

	m0+=m0_2*w2;
	m1+=m1_2*w2;
	m2+=m2_2*w2;

	
	v_model o;
	o.pos=skinning_pos(v.P.xyz,m0,m1,m2);
	o.norm=skinning_dir(v.N,m0,m1,m2);
	o.T=skinning_dir(v.T,m0,m1,m2);
	o.B=skinning_dir(v.B,m0,m1,m2);
	o.tc=v.tc		*(16.f/32768.f);
#ifdef SKIN_COLOR
	o.rgb_tint=float3	(2,0,0);
	if (id_0==id_1)	o.rgb_tint=float3(1,2,0);
#endif
	return o;
}

v_model skinning_3lq 	(v_model_skinned_3	v)
{
 return skinning_3(v);
}

v_model skinning_4 	(v_model_skinned_4	v)
{
	float id[4];
	float4	m[4][3];
	for (int i=0;i<4;++i)
	{	
		id[i]=v.ind[i]*255+0.3;
		for (int j=0;j<3;++j)
			m[i][j]=sbones_array[id[i]+j];
	}

	float w[4] = {v.N.w,v.T.w,v.B.w,0.0};
	w[3]=1.0-w[0]-w[1]-w[2];

	float4  m0=m[0][0]*w[0];
	float4  m1=m[0][1]*w[0];
	float4  m2=m[0][2]*w[0];

	for (int i=1;i<4;++i)
	{
		m0+=m[i][0]*w[i];
		m1+=m[i][1]*w[i];
		m2+=m[i][2]*w[i];
	}

	v_model o;
	o.pos=skinning_pos(v.P.xyz,m0,m1,m2);
	o.norm=skinning_dir(v.N,m0,m1,m2);
	o.T=skinning_dir(v.T,m0,m1,m2);
	o.B=skinning_dir(v.B,m0,m1,m2);
	o.tc=v.tc		*(16.f/32768.f);
#ifdef SKIN_COLOR
	o.rgb_tint=float3	(2,0,0);
	if (id_0==id_1)	o.rgb_tint=float3(1,2,0);
#endif
	return o;
}

v_model skinning_4lq 	(v_model_skinned_4	v)
{
 return skinning_4(v);
}

#endif
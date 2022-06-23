#ifndef	SHADOW_H
#define SHADOW_H

#include "common.h"




Texture2D	s_smap:register(ps,t0);

Texture2D<float>	s_smap_minmax;
#include "gather.ps"

SamplerComparisonState		smp_smap;
sampler		smp_jitter;

Texture2D jitter0, jitter1, jitterMipped;

#ifndef USE_ULTRA_SHADOWS
#define	KERNEL	0.6f
#else
#define	KERNEL	1.0f
#endif

float modify_light(float l)
{
   return (l>0.7?1.0:lerp(0.0,1.0,saturate(l/0.7)));
}




float sample_hw_pcf (float4 tc,float4 shift)
{
	static const float 	ts=KERNEL/float(SMAP_size);

	tc.xyz/=tc.w;
	tc.xy+=shift.xy*ts;

	return s_smap.SampleCmpLevelZero(smp_smap,tc.xy,tc.z).x;
}

#define GS2 3

float shadow_hw(float4 tc)
{
  	float	s0=sample_hw_pcf(tc,float4(-1,-1,0,0));
  	float	s1=sample_hw_pcf(tc,float4(+1,-1,0,0));
  	float	s2=sample_hw_pcf(tc,float4(-1,+1,0,0));
  	float	s3=sample_hw_pcf(tc,float4(+1,+1,0,0));

	return	(s0+s1+s2+s3)/4.h;
}

#if SUN_QUALITY>=4
#define FILTER_SIZE	11
#define FS  FILTER_SIZE
#define FS2 (FILTER_SIZE/2)

static const float W2[11][11]=
                 {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.0},
			       {0.0,0.2,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.2,0.0},
			       {0.0,0.2,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.2,0.0},
			       {0.0,0.2,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.2,0.0},
			       {0.0,0.2,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.2,0.0},
			       {0.0,0.2,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.2,0.0},
			       {0.0,0.2,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.2,0.0},
			       {0.0,0.2,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.2,0.0},
			       {0.0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			  };

static const float W1[11][11]=
                 {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.0,0.0},
			       {0.0,0.0,0.2,1.0,1.0,1.0,1.0,1.0,0.2,0.0,0.0},
			       {0.0,0.0,0.2,1.0,1.0,1.0,1.0,1.0,0.2,0.0,0.0},
			       {0.0,0.0,0.2,1.0,1.0,1.0,1.0,1.0,0.2,0.0,0.0},
			       {0.0,0.0,0.2,1.0,1.0,1.0,1.0,1.0,0.2,0.0,0.0},
			       {0.0,0.0,0.2,1.0,1.0,1.0,1.0,1.0,0.2,0.0,0.0},
			       {0.0,0.0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			  };

static const float W0[11][11]=
                 {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.1,0.1,0.1,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.1,1.0,0.1,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.1,0.1,0.1,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			       {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
			  };

float Fw(uint r,uint c,float fL)
{
	float CA = (1.0-fL);
	return CA*CA*CA*W0[r][c]+
	       3.0f*CA*CA*fL*W1[r][c]+
	       3.0f*fL*fL*CA*W2[r][c]+
                     fL*fL*fL;
} 

#define BLOCKER_FILTER_SIZE	11
#define BFS  BLOCKER_FILTER_SIZE
#define BFS2 (BLOCKER_FILTER_SIZE/2)

#define SUN_WIDTH 300.0f


float shadow_extreme_quality(float3 tc)
{
   float  s=0.0f, w=0.0f, avgBlockerDepth=0.0f, blockerCount=0.0f, fRatio;
   float2 stc=(SMAP_size*tc.xy)+float2(0.5,0.5);
   float2 tcs=floor(stc);
   float2 v0[FS2+1];
   float4 v1[FS2+1];

   float2 fc=stc-tcs;
   tc.xy=tc.xy-((1.0f/SMAP_size)*fc);
   tc.z-=0.0001f;

#if defined(SM_4_1)|| defined(SM_5)
    
    for(int row=-BFS2;row<=BFS2;row+=2)
    {
        for(int col=-BFS2;col<=BFS2;col+=2)
        {
            float4 d4=s_smap.Gather(smp_nofilter,tc.xy,int2(col,row));
            float4 b4=(tc.zzzz<=d4)?(0.0f).xxxx:(1.0f).xxxx;
			
            blockerCount+=dot(b4,(1.0f).xxxx);
            avgBlockerDepth+=dot(d4,b4);
   }
}
#else 
	uint vmask[FS+1];

    [unroll]for(uint col=0;col<=FS;++col)
		vmask[col]=uint(0);
	
	[unroll(11)]for(int row=-FS2;row<=FS2;row+=2)
    {
       [unroll]for(int col=-FS2;col<=FS2;col+=2)
        {
            float4 d4;

			d4.w=s_smap.SampleLevel(smp_nofilter,tc.xy,0,int2(col,row)).x;
			float b=(tc.z<=d4.w)?(0.0f):(1.0f);
			vmask[col+FS2+0]+=((tc.z<=d4.w)?(uint(1)<<uint(row+FS2+0)):uint(0));
			blockerCount  +=b;
            avgBlockerDepth+=d4.w*b;
			
			d4.z=s_smap.SampleLevel(smp_nofilter,tc.xy,0,int2(col+1,row)).x;
			b=(tc.z<=d4.z)? 0.0f:1.0f;
			vmask[col+FS2+1]+=((tc.z<=d4.z)?(uint(1)<<uint(row+FS2+0)):uint(0));
			blockerCount  +=b;
            avgBlockerDepth+=d4.z*b;
			
			d4.x=s_smap.SampleLevel(smp_nofilter,tc.xy,0,int2(col,row+1)).x;
			vmask[col+FS2+0]+=((tc.z<=d4.x)?(uint(1)<<uint(row+FS2+1)):uint(0));
			b=(tc.z<=d4.x)? 0.0f:1.0f;
			blockerCount  +=b;
            avgBlockerDepth+=d4.x*b;

			d4.y=s_smap.SampleLevel(smp_nofilter,tc.xy,0,int2(col+1,row+1)).x;
			vmask[col+FS2+1]+=((tc.z<=d4.y)?(uint(1)<<uint(row+FS2+1)):uint(0));
			b=(tc.z<=d4.y)? 0.0f:1.0f;
			blockerCount  +=b;
            avgBlockerDepth+=d4.y*b;
   }
}
#endif
   
   
   if(blockerCount>0.0)
   {
	   avgBlockerDepth/=blockerCount;
       fRatio=saturate(((tc.z-avgBlockerDepth)*SUN_WIDTH)/ avgBlockerDepth);
       fRatio*=fRatio;
	}
   else
	   fRatio=0.0;

   for(uint row=0;row<FS;++row)
   {
      for(uint col=0;col<FS;++col)
         w+=Fw(row,col,fRatio);
	}

    
    [unroll(11)]for(int row=-FS2;row<=FS2;row+=2)
    {
        [unroll]for(int col=-FS2;col<=FS2;col+=2)
        {
			int MASK = col+FS2, X = MASK/2, ROW = row+FS2;
#if (defined(SM_5))|| (defined(SM_4_1))
#ifdef SM_5
            v1[X]=s_smap.GatherCmpRed(smp_smap,tc.xy,tc.z,
                                                   int2(col,row));
#else 
			{float4 d4=s_smap.Gather(smp_linear,tc.xy,int2(col,row));
            v1[X]=(tc.zzzz<=d4)?(1.0f).xxxx:(0.0f).xxxx;}
#endif
#else
            v1[X].w=((vmask[MASK] & (uint(1)<<uint(ROW)))?1.0f:0.0f);
            v1[X].z=((vmask[MASK+1] & (uint(1)<<uint(ROW)))?1.0f:0.0f);
            v1[X].x=((vmask[MASK] & (uint(1)<<uint(ROW+1)))?1.0f:0.0f);
            v1[X].y=((vmask[MASK+1] & (uint(1)<<uint(ROW+1)))?1.0f:0.0f);
#endif
		  if(col==-FS2)
		  {
			 float FR = Fw(ROW,0,fRatio), FF = Fw(ROW,1,fRatio);
			 s+=(1-fc.y)*(v1[0].w*(FR-FR*fc.x)+v1[0].z*(fc.x*(FR-FF)+FF));
			 s+=(  fc.y)*(v1[0].x*(FR-FR*fc.x)+v1[0].y*(fc.x*(FR-FF)+FF));
			 if(row>-FS2)
			 {
				FR = Fw(ROW-1,0,fRatio), FF = Fw(ROW-1,1,fRatio);
				s+=(1-fc.y)*(v0[0].x*(FR-FR*fc.x)+v0[0].y*(fc.x*(FR-FF)+FF));
				s+=(  fc.y)*(v1[0].w*(FR-FR*fc.x)+v1[0].z*(fc.x*(FR-FF)+FF));
			}
		}
		  else if(col==FS2)
		  {
			 float FR = Fw(ROW,FS-2,fRatio), FF = Fw(ROW,FS-1,fRatio);
			 s+=(1-fc.y)*(v1[FS2].w*(fc.x*(FR-FF)+FF)+v1[FS2].z*fc.x*FF);
			 s+=(  fc.y)*(v1[FS2].x*(fc.x*(FR-FF)+FF)+v1[FS2].y*fc.x*FF);
			 if(row>-FS2)
			 {
				FR = Fw(ROW-1,FS-2,fRatio), FF = Fw(ROW-1,FS-1,fRatio);
				s+=(1-fc.y)*(v0[FS2].x*(fc.x*(FR-FF)+FF)+v0[FS2].y*fc.x*FF);
				s+=(  fc.y)*(v1[FS2].w*(fc.x*(FR-FF)+FF)+v1[FS2].z*fc.x*FF);
			}
		}
		  else
		  {
			 float FR = Fw(ROW,MASK-1,fRatio), FF = Fw(ROW,MASK,fRatio), wF = Fw(ROW,MASK+1,fRatio);
			 s+=(1-fc.y)*(v1[X].w*(fc.x*(FR-FF)+FF)+
						           v1[X].z*(fc.x*(FF-wF)+wF));
			 s+=(  fc.y)*(v1[X].x*(fc.x*(FR-FF)+FF)+
						           v1[X].y*(fc.x*(FF-wF)+wF));
			 if(row>-FS2)
			 {
				FR = Fw(ROW-1,MASK-1,fRatio), FF = Fw(ROW-1,MASK,fRatio), wF = Fw(ROW-1,MASK+1,fRatio);
				s+=(1-fc.y)*(v0[X].x*(fc.x*(FR-FF)+FF)+
							          v0[X].y*(fc.x*(FF-wF)+wF));
				s+=(  fc.y)*(v1[X].w*(fc.x*(FR-FF)+FF)+
							          v1[X].z*(fc.x*(FF-wF)+wF));
			}
	 }
		  if(row !=FS2)
			v0[X]=v1[X].xy;
	}
}

   return s/w;
}

float4 Fw(uint r,uint c)
{
	return float4(W0[r][c],W1[r][c],W2[r][c],1.0f);
}




float shadow_extreme_quality_fused(float3 tc)
{
    float4 s=(0.0f).xxxx;
    float2 stc=(SMAP_size*tc.xy)+float2(0.5,0.5);
    float2 tcs=floor(stc);
    float  w=0.0,avgBlockerDepth=0.0,blockerCount=0.0,fRatio;
    float4 v1[FS2+1];
    float2 v0[FS2+1];

    float2 fc=stc-tcs;
	const float ZN = 1.0f/SMAP_size;
    tc.xy=tc.xy-(fc*ZN);

    
    [unroll(FS)]for(int row=-FS2;row<=FS2;row+=2)
    {
        for(int col=-FS2;col<=FS2;col+=2)
        {
			int X = (col+FS2)/2;
			{
#ifndef PS_4
            float4 d4=s_smap.Gather(smp_nofilter,tc.xy+ZN*float2(col,row));
#else
			float4 d4;
			d4.w=s_smap.SampleLevel(smp_nofilter,tc.xy+ZN*float2(col,row),0).x;
			d4.z=s_smap.SampleLevel(smp_nofilter,tc.xy+ZN*float2(col+1,row),0).x;
			d4.y=s_smap.SampleLevel(smp_nofilter,tc.xy+ZN*float2(col+1,row+1),0).x;
			d4.x=s_smap.SampleLevel(smp_nofilter,tc.xy+ZN*float2(col,row+1),0).x;
#endif
            float4 b4=(tc.zzzz<=d4)?(0.0f).xxxx:(1.0f).xxxx;
            v1[X]=(tc.zzzz<=d4)?(1.0f).xxxx:(0.0f).xxxx;
            blockerCount+=dot(b4,(1.0).xxxx);
            avgBlockerDepth+=dot(d4,b4);
			}
          
            if(col==-FS2)
            {
				float4 FR = Fw(row+FS2,0), FF = Fw(row+FS2,1);
                s+=(1-fc.y)*(v1[0].w*(FR-
                                      FR*fc.x)+v1[0].z*
                                    (fc.x*(FR-
                                      FF)+
                                      FF));
                s+=(  fc.y)*(v1[0].x*(FR-
                                      FR*fc.x)+
                                      v1[0].y*(fc.x*(FR-
                                      FF)+
                                      FF));
                if(row>-FS2)
                {
					FR = Fw(row+FS2-1,0), FF = Fw(row+FS2-1,1);
                    s+=(1-fc.y)*(v0[0].x*(FR-
                                          FR*fc.x)+v0[0].y*
                                        (fc.x*(FR-
                                          FF)+
                                          FF));
                    s+=(  fc.y)*(v1[0].w*(FR-
                                          FR*fc.x)+v1[0].z*
                                        (fc.x*(FR-
                                          FF)+
                                          FF));
           }
       }
            else if(col==FS2)
            {
				float4 FR = Fw(row+FS2,FS-2), FF = Fw(row+FS2,FS-1);
                s+=(1-fc.y)*(v1[FS2].w*(fc.x*(FR-
                                      FF)+
                                      FF)+v1[FS2].z*fc.x*
                                      FF);
                s+=(  fc.y)*(v1[FS2].x*(fc.x*(FR-
                                      FF)+
                                      FF)+v1[FS2].y*fc.x*
                                      FF);
                if(row>-FS2)
                {
					FR = Fw(row+FS2-1,FS-2), FF = Fw(row+FS2-1,FS-1);
                    s+=(1-fc.y)*(v0[FS2].x*(fc.x*
                                        (FR-
                                          FF)+
                                          FF)+
                                          v0[FS2].y*fc.x*FF);
                    s+=(  fc.y)*(v1[FS2].w*(fc.x*
                                        (FR-
                                          FF)+
                                          FF)+
                                          v1[FS2].z*fc.x*FF);
           }
       }
            else
            {
				float4 FR = Fw(row+FS2,col+FS2-1), FF = Fw(row+FS2,col+FS2), wF = Fw(row+FS2,col+FS2+1);
                s+=(1-fc.y)*(v1[X].w*(fc.x*
                                    (FR-
                                      FF)+
                                      FF)+
                                      v1[X].z*(fc.x*
                                    (FF-
                                      wF)+
                                      wF));
                s+=(  fc.y)*(v1[X].x*(fc.x*
                                    (FR-
                                      FF)+
                                      FF)+
                                      v1[X].y*(fc.x*
                                    (FF-
                                      wF)+
                                      wF));
                if(row>-FS2)
                {
					FR = Fw(row+FS2-1,col+FS2-1), FF = Fw(row+FS2-1,col+FS2), wF = Fw(row+FS2-1,col+FS2+1);
                    s+=(1-fc.y)*(v0[X].x*(fc.x*
                                        (FR-
                                          FF)+
                                          FF)+
                                          v0[X].y*(fc.x*
                                        (FF-
                                          wF)+
                                          wF));
                    s+=(  fc.y)*(v1[X].w*(fc.x*
                                        (FR-
                                          FF)+
                                          FF)+
                                          v1[X].z*(fc.x*
                                        (FF-
                                          wF)+
                                          wF));
           }
       }
            
            if(row !=FS2)
                v0[X]=v1[X].xy;
   }
}

    
    if(blockerCount>0.0)
    {
        avgBlockerDepth/=blockerCount;
        fRatio=saturate(((tc.z-avgBlockerDepth)*SUN_WIDTH)/ avgBlockerDepth);
        fRatio*=fRatio;
	}
    else
        fRatio=0.0;

    
    for(uint row=0;row<FS;++row)
    {
       for(uint col=0;col<FS;++col)
          w+=Fw(row,col,fRatio);
	}

	float CM = (1.0f-fRatio);
    return dot(s,float4(CM*CM*CM,
						 3.0f*CM*CM*fRatio,
						 3.0f*fRatio*fRatio*CM,
						 fRatio*fRatio*fRatio))/w;
}
#endif

#ifdef SM_4_1

float dx10_1_hw_hq_7x7(float3 tc)
{
   float  s=0.0f;
   float2 stc=(SMAP_size*tc.xy)+float2(0.5,0.5);
   float2 tcs=floor(stc);
   float2 fc;

   fc.xy=stc-tcs;
   tc.xy=tcs*(1.0/SMAP_size);
   
   
   for(int row=-GS2;row<=GS2;row+=2)
   {
       [unroll]for(int col=-GS2;col<=GS2;col+=2)
       {
            float4 v=(tc.zzzz<=s_smap.Gather(smp_nofilter,tc.xy,int2(col,row)))?(1.0).xxxx:(0.0).xxxx;
            
            if(row==-GS2)
            {
                if(col==-GS2)
                    s+=dot(float4(1.0-fc.x,1.0,1.0-fc.y,(1.0-fc.x)*(1.0-fc.y)),v);
                else if(col==GS2)
                    s+=dot(float4(1.0f,fc.x,fc.x*(1.0-fc.y),1.0-fc.y),v);
                else 
                    s+=dot(float4(1.0,1.0,1.0-fc.y,1.0-fc.y),v);
       }
            else if(row==GS2)
            {
                if(col==-GS2)
                    s+=dot(float4((1.0-fc.x)*fc.y,fc.y,1.0,(1.0-fc.x)),v);
                else if(col==GS2)
                    s+=dot(float4(fc.y,fc.x*fc.y,fc.x,1.0),v);
                else 
                    s+=dot(float4(fc.yy,1.0,1.0),v);
       }
            else 
            {
                if(col==-GS2)
                    s+=dot(float4((1.0-fc.x),1.0,1.0,(1.0-fc.x)),v);
                else if(col==GS2)
                    s+=dot(float4(1.0,fc.x,fc.x,1.0),v);
                else 
                    s+=dot((1.0).xxxx,v);
       }
   }
}
  
   return s*(1.0/49.0);
}

#endif

float dx10_0_hw_hq_7x7(float4 tc)
{
   tc.xyz/=tc.w;

   float  s=0.0;
   float2 stc=(SMAP_size*tc.xy)+float2(0.5,0.5);
   float2 fc;

   fc=stc-floor(stc);
   tc.xy=tc.xy-(fc*(1.0/SMAP_size));

   float2 pwAB=((2.0).xx-fc);
   float2 tcAB=(1.0/SMAP_size).xx/pwAB;
   float2 tcM=(0.5/SMAP_size).xx;
   float2 pwGH=((1.0).xx+fc);
   float2 tcGH=(1.0/SMAP_size)*(fc/pwGH);

   for(int row=-GS2;row<=GS2;row+=2)
   {
      for(int col=-GS2;col<=GS2;col+=2)
	  {
		if(row==-GS2)
		{
			if(col==-GS2)
				s+=(pwAB.x*pwAB.y)*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+tcAB,tc.z,int2(col,row)).x;
			else if(col==GS2)
				s+=(pwGH.x*pwAB.y)*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+float2(tcGH.x,tcAB.y),tc.z,int2(col,row)).x;
			else 
				s+=( 2.0*pwAB.y)*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+float2(tcM.x,tcAB.y),tc.z,int2(col,row)).x;
}
		else if(row==GS2)
		{
			if(col==-GS2)
				s+=(pwAB.x*pwGH.y)*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+float2(tcAB.x,tcGH.y),tc.z,int2(col,row)).x;
			else if(col==GS2)
				s+=(pwGH.x*pwGH.y)*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+tcGH,tc.z,int2(col,row)).x;
			else 
				s+=( 2.0*pwGH.y)*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+float2(tcM.x,tcGH.y),tc.z,int2(col,row)).x;
}
		else 
		{
			if(col==-GS2)
				s+=(pwAB.x*2.0 )*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+float2(tcAB.x,tcM.y),tc.z,int2(col,row)).x;
			else if(col==GS2)
				s+=(pwGH.x*2.0 )*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+float2(tcGH.x,tcM.y),tc.z,int2(col,row)).x;
			else 
				s+=4.0*s_smap.SampleCmpLevelZero(smp_smap,tc.xy+tcM,tc.z,int2(col,row)).x;
}
 }
}

    return s/49.0;
}

#ifdef SM_MINMAX
bool cheap_reject(float3 tc,inout bool full_light)
{
   float4 plane0=sm_minmax_gather(tc.xy,int2(-1,-1));
   float4 plane1=sm_minmax_gather(tc.xy,int2(1,-1));
   float4 plane2=sm_minmax_gather(tc.xy,int2(-1,1));
   float4 plane3=sm_minmax_gather(tc.xy,int2(1,1));
   bool plane=all((plane0>=(0).xxxx)*(plane1>=(0).xxxx)*(plane2>=(0).xxxx)*(plane3>=(0).xxxx));

   [flatten] if(!plane)
   {
      bool no_plane=all((plane0<(0).xxxx)*(plane1<(0).xxxx)*(plane2<(0).xxxx)*(plane3<(0).xxxx));
      float4 z =(tc.z-0.0005).xxxx;
      bool reject=all((z>-plane0)*(z>-plane1)*(z>-plane2)*(z>-plane3));
      [flatten] if(no_plane && reject)
      {
         full_light=false;
         return true;
	  }
      else
        return false;
}
   else 
   {
      
      static const float scale=float(SMAP_size/4);
      float2 fc=frac(tc.xy*scale);
      float  z=lerp(lerp(plane0.y,plane1.x,fc.x),lerp(plane2.z,plane3.w,fc.x),fc.y);

      
      full_light=((tc.z-0.0001)<=z);

      return true;
}
}

#endif	

float shadow_hw_hq(float4 tc)
{
#ifdef SM_MINMAX
   bool   full_light=false;
   bool   cheap_path=cheap_reject(tc.xyz/tc.w,full_light);

   [branch] if(cheap_path)
   {
      [branch] if(full_light==true)
         return 1.0;
      else
         return sample_hw_pcf(tc,(0).xxxx);
}
   else
   {
#if SUN_QUALITY>=4 
      return shadow_extreme_quality(tc.xyz/tc.w);
#else 
#ifdef SM_4_1
      return dx10_1_hw_hq_7x7(tc.xyz/tc.w);
#else 
      return dx10_0_hw_hq_7x7(tc);
#endif 
#endif 
}
#else 
#if SUN_QUALITY>=4 
      return shadow_extreme_quality(tc.xyz/tc.w);
#else 
#ifdef SM_4_1
      return dx10_1_hw_hq_7x7(tc.xyz/tc.w);
#else 
      return dx10_0_hw_hq_7x7(tc);
#endif 
#endif 
#endif 
}

float4 	test 		(float4 tc,float2 offset)
{
	tc.xyz/=tc.w;
	tc.xy+=offset;
	return s_smap.SampleCmpLevelZero(smp_smap,tc.xy,tc.z).x;
}

half 	shadowtest_sun 	(float4 tc)			
{
	
	const 	float 	scale=(0.7f/float(SMAP_size));


	float2 	tc_J=frac(tc.xy/tc.w*SMAP_size/4.0f)*.5f;
	float4	J0=jitter0.Sample(smp_jitter,tc_J)*scale;
	const float k=.5f/float(SMAP_size);
	half4 r;
	r.x=test(tc,J0.xy+half2(-k,-k)).x;
	r.y=test(tc,J0.wz+half2(k,-k)).y;
	r.z=test(tc,-J0.xy+half2(-k,k)).z;
	r.w=test(tc,-J0.wz+half2(k,k)).x;

	return	dot(r,1.h/4.h);
}

half 	shadow_high 	(float4 tc)			
{
	float k=(0.5f/float(SMAP_size));

	float2 	tc_J=frac(tc.xy/tc.w*SMAP_size/4.0f)*.5f;
	float4	J0=jitter0.Sample(smp_jitter,tc_J)*k;

	k=1.f/float(SMAP_size);
	half4	r;
	r.x=test(tc,J0.xy+half2(-k,-k)).x;
	r.y=test(tc,J0.wz+half2(k,-k)).y;

	r.z=test(tc,J0.xy+half2(-k,k)).z;
	r.w=test(tc,J0.wz+half2(k,k)).x;

	k=1.3f/float(SMAP_size);
	half4	r1;
	r1.x=test(tc,-J0.xy+half2(-k,0)).x;
	r1.y=test(tc,-J0.wz+half2(0,-k)).y;

	r1.z=test(tc,-2*J0.xy+half2(k,0)).z;
	r1.w=test(tc,-2*J0.wz+half2(0,k)).x;

	return (r.x+r.y+r.z+r.w+r1.x+r1.y+r1.z+r1.w)*1.h/8.h;
}

float shadow(float4 tc)
{
#ifdef USE_ULTRA_SHADOWS
#	ifdef SM_MINMAX
		return modify_light(shadow_hw_hq(tc));
#	else
		return shadow_hw_hq(tc);
#	endif
#else
#	if SUN_QUALITY>=2 
		
		return shadow_hw		(tc);
#	else
		return shadow_hw		(tc);
#	endif
#endif
}

float shadow_volumetric(float4 tc)
{
	return sample_hw_pcf	(tc,float4(-1,-1,0,0));
}


#ifdef SM_MINMAX





float shadow_dx10_1(float4 tc)
{
   return shadow(tc);
}

float shadow_dx10_1_sunshafts(float4 tc)
{
   float3 t   =tc.xyz/tc.w;
   float minmax=s_smap_minmax.SampleLevel(smp_nofilter,t,0).x;
   bool   umbra=((minmax.x<0)&& (t.z>-minmax.x));

   [branch] if(umbra)
   {
      return 0.0;
	}
   else
      return shadow_hw(tc);
}

#endif







float 	shadowtest 	(float4 tc,float4 tcJ)				
{
	float4	r;

	const 	float 	scale=(2.7f/float(SMAP_size));



	tcJ.xy	/=tcJ.w;
	float4	J0=jitter0.Sample(smp_jitter,tcJ)*scale;
	float4	J1=jitter1.Sample(smp_jitter,tcJ)*scale;

		r.x=test 	(tc,J0.xy).x;
		r.y=test 	(tc,J0.wz).y;
		r.z=test	(tc,J1.xy).z;
		r.w=test	(tc,J1.wz).x;

	return	dot(r,1.h/4.h);
}

float 	shadow_rain 	(float4 tc,float2 tcJ)			
{
	float4	r;

	const 	float 	scale=(4.0f/float(SMAP_size));
	float4	J0=jitter0.Sample(smp_linear,tcJ)*scale;
	float4	J1=jitter1.Sample(smp_linear,tcJ)*scale;

	r.x=test 	(tc,J0.xy).x;
	r.y=test 	(tc,J0.wz).y;
	r.z=test	(tc,J1.xy).z;
	r.w=test	(tc,J1.wz).x;

	return	dot(r,1.h/4.h);
}


#ifdef USE_SUNMASK	
float3x4 m_sunmask;
float sunmask(float4 P)
{
	float2 		tc=mul(m_sunmask,P);
	return 		s_lmap.Sample(smp_linear,tc).w;
}
#else
float sunmask(){return 1.h;}
#endif

uniform float4x4	m_shadow;

#endif
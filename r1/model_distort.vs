#include "common.h"
#include "skin.h"

struct vf
{
  float4 hpos :POSITION;
  float2 tc0 :TEXCOORD0;
  float4 c0 :COLOR0;
};

vf   _main (v_model v)
{
  vf     o;

  o.hpos=mul      (m_WVP,v.pos);
  o.tc0=v.tc.xy;

  float3  dir_v=normalize    (mul(m_WV,v.pos));
  float3   norm_v=normalize     (mul(m_WV,v.norm));
  float   fade=1-abs      (dot(dir_v,norm_v));
  o.c0=fade;

  return o;
}

#define SKIN_VF vf
#include "skin_main.h"
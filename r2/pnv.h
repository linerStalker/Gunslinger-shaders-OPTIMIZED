






#define NV_BRIGHTNESS 5.0


#define NV_FLICKERING
#define NV_NOISE

#define NV_SCANLINES


#define FLICKERING_INTENSITY 0.003    
#define FLICKERING_FREQ 60.0          
#define NOISE_INTENSITY 0.13          
#define SCANLINES_INTENSITY 0.015     
#define VIGNETTE_RADIUS 1.0           


uniform	float4		screen_res;
uniform	float4 		m_zoom_deviation;

float4 calc_night_vision_effect(float2 tc0,float4 color,float3 NV_COLOR)
{
    float lum=dot(color.rgb,float3(0.3f,0.38f,0.22f)*NV_BRIGHTNESS);
    color.rgb=m_zoom_deviation.z*NV_COLOR*lum;
    
    
    float noise=frac(sin(dot(tc0,float2(12.0,78.0)+(timers.x*1.17f)))*43758.0);
    
    
    
    #ifdef NV_SCANLINES
    color+=SCANLINES_INTENSITY*sin(tc0.y*screen_res.y*2.0);
    #endif
    
    
    #ifdef NV_NOISE
    color+=noise*NOISE_INTENSITY;
    #endif
    
    
    #ifdef NV_FLICKERING
    color+=FLICKERING_INTENSITY*sin(timers.x*FLICKERING_FREQ);
    #endif
    
    
    #ifdef NV_VIGNETTE
	color*=VIGNETTE_RADIUS-(distance(tc0.xy,float2(0.5f,0.5f)));
   	#endif
	
   	return color;
}

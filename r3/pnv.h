uniform	float4		screen_res;
uniform	float4 		m_zoom_deviation;

float4 calc_night_vision_effect(float2 tc0,float4 color,float3 NV_COLOR)
{
    float lum=dot(color.rgb,float3(0.3f,0.38f,0.22f)*5.0);
    color.rgb=m_zoom_deviation.z*NV_COLOR*lum;
    float noise=frac(sin(dot(tc0,float2(12.0,78.0)+(timers.x*1.17f)))*43758.0);

    color+=0.015*sin(tc0.y*screen_res.y*2.0);
    color+=noise*0.13;
    color+=0.003*sin(timers.x*60.0);
	//Виньетка
//	color*=1.0-(distance(tc0.xy,float2(0.5f,0.5f)));
	
   	return color;
}
#ifndef	DOF_H_INCLUDED
#define	DOF_H_INCLUDED



#ifndef	USE_DOF

half3	dof(float2 center)
{
	half3 	img=tex2D		(s_image,center);
	return	img;
}

#else	


half4	dof_params;
half3	dof_kernel;

half DOFFactor(half depth)
{
	half	dist_to_focus=depth-dof_params.y;
	half 	blur_far=saturate(dist_to_focus
					/ (dof_params.z-dof_params.y));
	half 	blur_near=saturate(dist_to_focus
					/ (dof_params.x-dof_params.y));
	half 	blur=blur_near+blur_far;
	blur*=blur;
	return blur;
}



#define MAXCOF		7.h
#define EPSDEPTH	0.0001h
half3	dof(float2 center)
{
	
	half 	depth=tex2D(s_position,center).z;
	if (depth<=EPSDEPTH)	depth=dof_params.w;
	half	blur=DOFFactor(depth);
	
	half2 	scale=half2	(.5f/1024.h,.5f/768.h)*(dof_kernel.z*blur);
	
	half2 	o  [12];
		o[0]=half2(-0.326212f ,-0.405810f)*scale;
		o[1]=half2(-0.840144f ,-0.073580f)*scale;
		o[2]=half2(-0.695914f ,0.457137f)*scale;
		o[3]=half2(-0.203345f ,0.620716f)*scale;
		o[4]=half2(0.962340f ,-0.194983f)*scale;
		o[5]=half2(0.473434f ,-0.480026f)*scale;
		o[6]=half2(0.519456f ,0.767022f)*scale;
		o[7]=half2(0.185461f ,-0.893124f)*scale;
		o[8]=half2(0.507431f ,0.064425f)*scale;
		o[9]=half2(0.896420f ,0.412458f)*scale;
		o[10]=half2(-0.321940f ,-0.932615f)*scale;
		o[11]=half2(-0.791559f ,-0.597710f)*scale;

	
	half3	sum=tex2D(s_image,center);
	half 	contrib=1.h;

   	for (int i=0;i<12;++i)
	{
		float2 	tap=center+o[i];
		half4	tap_color=tex2D	(s_image,tap);
		half 	tap_depth=tex2D	(s_position,tap).z;
		if (tap_depth<=EPSDEPTH)	tap_depth=dof_params.w;
		half 	tap_contrib=DOFFactor(tap_depth);
		sum+=tap_color	*tap_contrib;
		contrib+=tap_contrib;
}

	return 	half3	(sum/contrib);
}

#endif	

#endif	
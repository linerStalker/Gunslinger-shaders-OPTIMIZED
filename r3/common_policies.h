#ifndef	common_policies_h_included
#define	common_policies_h_included


#ifndef	ISAMPLE
#define ISAMPLE 0
#endif	


#ifdef 	MSAA_OPTIMIZATION
#undef	ISAMPLE
#define ISAMPLE	iSample
#endif	



#ifdef GBUFFER_OPTIMIZATION
	#define	GLD_P(_tc,_pos2d,_iSample)_tc,_pos2d,_iSample
#else	
	#define	GLD_P(_tc,_pos2d,_iSample)_tc,_iSample
#endif	



#ifdef USE_MSAA
#	ifdef	GBUFFER_OPTIMIZATION
#		define	CS_P(_P,_N,_tc0,_tcJ,_pos2d,_iSample)_P,_N,_tc0,_tcJ,_pos2d,_iSample
#	else	
#		define	CS_P(_P,_N,_tc0,_tcJ,_pos2d,_iSample)_P,_N,_tc0,_tcJ,_iSample
#	endif	
#else
#	ifdef	GBUFFER_OPTIMIZATION
#		define	CS_P(_P,_N,_tc0,_tcJ,_pos2d,_iSample)_P,_N,_tc0,_tcJ,_pos2d
#	else	
#		define	CS_P(_P,_N,_tc0,_tcJ,_pos2d,_iSample)_P,_N,_tc0,_tcJ
#	endif
#endif

#endif	
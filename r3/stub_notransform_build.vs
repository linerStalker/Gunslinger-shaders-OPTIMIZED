#include "common_iostructs.h"

float4		screen_res;



v2p_build main (v_build I)
{
	v2p_build O;

	{

		I.P.xy+=0.5f;


		O.HPos.x=I.P.x*screen_res.z*2-1;
		O.HPos.y=(I.P.y*screen_res.w*2-1)*-1;
		O.HPos.zw=I.P.zw;
}

	O.Tex0=I.Tex0;
	O.Tex1=I.Tex1;
	O.Tex2=I.Tex2;
	O.Tex3=I.Tex3;

 	return O;
}
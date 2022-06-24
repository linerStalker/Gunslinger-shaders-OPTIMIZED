#include "common_iostructs.h"



v2p_TL main (v_TL I)
{
	v2p_TL O;

	O.HPos=I.P;
	O.Tex0=I.Tex0;
	
	O.Color=I.Color.bgra;

 	return O;
}
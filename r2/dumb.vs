#include "common.h"

struct 	v2p
{
	float4 	hpos:		POSITION;
};



v2p 	main	(float4 P:	POSITION)
{
	v2p 		O;
	O.hpos=mul	(m_WVP,  	P);
 	return	O;
}
FXVS;

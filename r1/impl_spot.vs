#include "common.h"

vf_spot main (v_lmap v)
{
	vf_spot		o;

	o.hpos=mul		(m_VP,v.P);//xform,input in world coords
	o.tc0=unpack_tc_base	(v.uv0.xy,v.T.w,v.B.w);
	o.color=calc_spot 	(o.tc1,o.tc2,v.P,unpack_bx2(v.N));//just hemisphere

	return o;
}

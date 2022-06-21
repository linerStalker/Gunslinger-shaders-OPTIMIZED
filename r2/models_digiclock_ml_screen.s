function normal		(shader,t_base,t_second,t_detail)
	shader:begin	("deffer_model_flat","model_digiclock_ml")
			:fog		(false)
			:emissive 	(true)
	shader:sampler	("s_base"):texture	(t_base)
	shader:sampler  ("s_lmap"):texture("$alphadxt1")
end

function l_special	(shader,t_base,t_second,t_detail)
	shader:begin	("shadow_direct_model","accum_emissivel")
			:zb 		(true,false)
			:fog		(false)
			:emissive 	(true)
end

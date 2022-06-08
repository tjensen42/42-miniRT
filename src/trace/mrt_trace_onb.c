#include "mrt_trace_onb.h"

// in must be normalized
t_onb	onb_build(t_vec3 in)
{
	t_onb	onb;

	onb.w = in;
	if (fabs(vec3_dot(onb.w, (t_vec3){1.0, 0.0, 0.0})) > 0.9)
		onb.v = vec3_norm(vec3_cross(onb.w, (t_vec3){0.0, 1.0, 0.0}));
	else
		onb.v = vec3_norm(vec3_cross(onb.w, (t_vec3){1.0, 0.0, 0.0}));
	onb.u = vec3_cross(onb.w, onb.v);
	return (onb);
}

t_vec3	onb_transform(t_onb onb, t_vec3 in)
{
	return (vec3_norm(vec3_lin_comb(1.0,
				vec3_lin_comb(in.x, onb.u, in.y, onb.v), in.z, onb.w)));
}

#include "mrt_trace.h"

t_vec3	normal_plane(t_list *obj, t_hit *hit __attribute__((unused)))
{
	return (obj_cont(obj)->pl.dir);
}

t_vec3	normal_disc(t_list *obj, t_hit *hit __attribute__((unused)))
{
	return (obj_cont(obj)->di.dir);
}

// statt vec3_normalize /r
t_vec3	normal_sphere(t_list *obj, t_hit *hit)
{
	return (vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->sp.pos)));
}

// ohne h möglich?
t_vec3	normal_tube(t_list *obj, t_hit *hit)
{
	double	h;
	t_vec3	normal;

	h = vec3_scalar_product(
			vec3_subtract(hit->p,
				obj_cont(obj)->tb.pos), obj_cont(obj)->tb.dir);
	normal = vec3_normalize(
			vec3_subtract(hit->p,
				vec3_add(obj_cont(obj)->tb.pos,
					vec3_scale(h, obj_cont(obj)->tb.dir))));
	return (normal);
}

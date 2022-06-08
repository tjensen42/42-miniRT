#include "mrt_trace.h"

t_vec3	normal_plane(t_list *obj, t_hit *hit __attribute__((unused)))
{
	return (obj_cont(obj)->pl.dir);
}

t_vec3	normal_disc(t_list *obj, t_hit *hit __attribute__((unused)))
{
	return (obj_cont(obj)->di.dir);
}

t_vec3	normal_sphere(t_list *obj, t_hit *hit)
{
	return (vec3_scale(1.0 / obj_cont(obj)->sp.radius,
			vec3_sub(hit->p, obj_cont(obj)->sp.pos)));
}

t_vec3	normal_tube(t_list *obj, t_hit *hit)
{
	t_vec3	normal;
	double	h;

	h = vec3_dot(vec3_sub(hit->p, obj_cont(obj)->tb.pos),
			obj_cont(obj)->tb.dir);
	normal = vec3_norm(vec3_sub(hit->p, vec3_add(obj_cont(obj)->tb.pos,
					vec3_scale(h, obj_cont(obj)->tb.dir))));
	return (normal);
}

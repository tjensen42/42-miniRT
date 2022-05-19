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
	// statt vec3_normalize /r
	return (vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->sp.pos)));
}

t_vec3	normal_tube(t_list *obj, t_hit *hit)
{
	t_vec3		normal;
	double		h;

	// ohne h möglich?
	h = vec3_scalar_product(vec3_subtract(hit->p, obj_cont(obj)->tb.pos), obj_cont(obj)->tb.dir);
	normal = vec3_normalize(vec3_subtract(hit->p, vec3_add(obj_cont(obj)->tb.pos, vec3_scale(h, obj_cont(obj)->tb.dir))));
	return (normal);
}

t_vec3	normal_rectangle(t_list *obj, t_hit *hit __attribute__((unused)))
{
	t_vec3	tmp_normal;
	double	tmp;
	double	sine;
	double	cosine;

	tmp_normal = obj_cont(obj)->rt.dir;
	if (obj_cont(obj)->rt.rot.x != 0.0)
	{
		sine = sin(obj_cont(obj)->rt.rot.x * DEG2RAD);
		cosine = cos(obj_cont(obj)->rt.rot.x * DEG2RAD);
		tmp = cosine * tmp_normal.y + sine * tmp_normal.z;
		tmp_normal.z = - sine * tmp_normal.y + cosine * tmp_normal.z;
		tmp_normal.y = tmp;
	}
	if (obj_cont(obj)->rt.rot.y != 0.0)
	{
		sine = sin(obj_cont(obj)->rt.rot.y * DEG2RAD);
		cosine = cos(obj_cont(obj)->rt.rot.y * DEG2RAD);
		tmp = cosine * tmp_normal.x - sine * tmp_normal.z;
		tmp_normal.z = sine * tmp_normal.x + cosine * tmp_normal.z;
		tmp_normal.x = tmp;
	}
	if (obj_cont(obj)->rt.rot.z != 0.0)
	{
		sine = sin(obj_cont(obj)->rt.rot.z * DEG2RAD);
		cosine = cos(obj_cont(obj)->rt.rot.z * DEG2RAD);
		tmp = cosine * tmp_normal.x + sine * tmp_normal.y;
		tmp_normal.y = - sine * tmp_normal.x + cosine * tmp_normal.y;
		tmp_normal.x = tmp;
	}
	return (tmp_normal);
}

#include "mrt_trace.h"

t_vec3	normal_plane(t_list *obj, t_hit *hit)
{
	return (obj_cont(obj)->pl.dir);
}

t_vec3	normal_sphere(t_list *obj, t_hit *hit)
{
	t_vec3		normal;

	// statt vec3_normalize /r
	normal = vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->sp.pos));
	return (normal);
}

t_vec3	normal_cylinder(t_list *obj, t_hit *hit)
{
	t_vec3		normal;
	double		h;

	h = vec3_scalar_product(vec3_subtract(hit->p, obj_cont(obj)->cy.pos), obj_cont(obj)->cy.dir);
	if (h < 1e-6)
		return (vec3_scale(-1.0, obj_cont(obj)->cy.dir));
	if (h > obj_cont(obj)->cy.height - 1e-6)
		return (obj_cont(obj)->cy.dir);
	normal = vec3_normalize(vec3_subtract(hit->p, vec3_add(obj_cont(obj)->cy.pos, vec3_scale(h, obj_cont(obj)->cy.dir))));
	return (normal);
}

t_vec3	normal_rectangle(t_list *obj, t_hit *hit)
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

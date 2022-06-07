#include "mrt_trace.h"

double	intersec_plane(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	double	t;
	t_plane	*plane;

	plane = &(obj_cont(obj)->pl);
    double denom = vec3_scalar_product(plane->dir, ray->dir);
    if (fabs(denom) > 1e-6) //1e-6
	{
        t_vec3	p0l0 = vec3_subtract(obj_cont(obj)->pl.pos, ray->pos);
        t = (double)vec3_scalar_product(p0l0, plane->dir) / denom;
		if (t > t_min && t < t_max)
        	return (t);
    }
	return (-1);
}

double	intersec_sphere(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_vec3		cc;
	t_sphere	*sphere;
	// double		a;
	double		b_half;
	double		c;
	double		discriminant;
	double		discriminant_sqrt;
	double		t;

	sphere = &(obj_cont(obj)->sp);
	cc = vec3_subtract(ray->pos, obj_cont(obj)->sp.pos);
	// a = vec3_scalar_product(ray->dir, ray->dir);
	// a = 1; // da ray.dir normiert
	b_half = vec3_scalar_product(ray->dir, cc);
	c = vec3_scalar_product(cc, cc) - sphere->radius * sphere->radius;
	discriminant = b_half * b_half - c;
	if (discriminant < 0)
		return (-1);
	discriminant_sqrt = sqrt(discriminant);
	t = (-b_half - discriminant_sqrt);
	if (t < t_min || t > t_max)
	{
		t = (-b_half + discriminant_sqrt);
		if (t < t_min || t > t_max)
			return (-1);
	}
	return (t);
}

double	intersec_disc(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	double	t;

    double denom = vec3_scalar_product(obj_cont(obj)->di.dir, ray->dir);
    if (fabs(denom) > 1e-6) //1e-6
	{
        t_vec3	p0l0 = vec3_subtract(obj_cont(obj)->di.pos, ray->pos);
        t = (double)vec3_scalar_product(p0l0, obj_cont(obj)->di.dir) / denom;
		if (t > t_min && t < t_max)
		{
			if (vec3_distance(obj_cont(obj)->di.pos, vec3_linear_comb(1.0, ray->pos, t, ray->dir)) <= obj_cont(obj)->di.radius)
        		return (t);
		}
    }
	return (-1);
}

double	intersec_tube(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_tube	*tb;
	double	discriminant;
	double	discriminant_sqrt;
	double	a, b, c, t, h;
	t_vec3	tmp, tmp2;

	tb = &(obj_cont(obj)->tb);
	tmp = vec3_vector_product(ray->dir, tb->dir);
	a = vec3_scalar_product(tmp, tmp);
	tmp2 = vec3_vector_product(vec3_subtract(ray->pos, obj_cont(obj)->tb.pos), tb->dir);
	b = 2.0 * vec3_scalar_product(tmp, tmp2);
	c = vec3_scalar_product(tmp2, tmp2) - tb->radius * tb->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	discriminant_sqrt = sqrt(discriminant);
	t = (-b - discriminant_sqrt) / (2 * a);
	h = vec3_scalar_product(vec3_subtract(vec3_linear_comb(1.0, ray->pos, t, ray->dir), obj_cont(obj)->tb.pos), tb->dir);
	if (t < t_min || t > t_max || fabs(h) > tb->height / 2.0)
	{
		t = (-b + discriminant_sqrt) / (2 * a);
		h = vec3_scalar_product(vec3_subtract(vec3_linear_comb(1.0, ray->pos, t, ray->dir), obj_cont(obj)->tb.pos), tb->dir);
		if (t < t_min || t > t_max || fabs(h) > tb->height / 2.0)
			return (-1);
	}
	return (t);
}

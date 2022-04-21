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

static double cylinder_caps(t_obj *cap, t_ray *ray, double t_min, double t_max, double radius)
{
	double	t;

	t = intersec_plane(ft_lstnew(cap), ray, t_min, t_max);
	if (vec3_distance(cap->pl.pos, vec3_linear_comb(1.0, ray->pos, t, ray->dir)) > radius)
		return (-1);
	return (t);
}

static double	cylinder_lateral(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_cylinder	*cy;
	double	discriminant;
	double	discriminant_sqrt;
	double	a, b, c, t, h;
	t_vec3	tmp, tmp2;

	cy = &(obj_cont(obj)->cy);
	tmp = vec3_vector_product(ray->dir, cy->dir);
	a = vec3_scalar_product(tmp, tmp);
	tmp2 = vec3_vector_product(vec3_subtract(ray->pos, obj_cont(obj)->cy.pos), cy->dir);
	b = 2.0 * vec3_scalar_product(tmp, tmp2);
	c = vec3_scalar_product(tmp2, tmp2) - cy->radius * cy->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	discriminant_sqrt = sqrt(discriminant);
	t = (-b - discriminant_sqrt) / (2 * a);
	h = vec3_scalar_product(vec3_subtract(vec3_linear_comb(1.0, ray->pos, t, ray->dir), obj_cont(obj)->cy.pos), cy->dir);
	if (t < t_min || t > t_max || h < 0 || h > cy->height)
	{
		t = (-b + discriminant_sqrt) / (2 * a);
		h = vec3_scalar_product(vec3_subtract(vec3_linear_comb(1.0, ray->pos, t, ray->dir), obj_cont(obj)->cy.pos), cy->dir);
		if (t < t_min || t > t_max || h < 0 || h > cy->height)
			return (-1);
	}
	return (t);
}

double	intersec_cylinder(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	double	t_min_cy, t_cap_bottom, t_cap_top, t_lateral;
	t_obj	cap;

	cap.pl.pos = obj_cont(obj)->cy.pos;
	cap.pl.dir = vec3_scale(-1.0, obj_cont(obj)->cy.dir);
	t_cap_bottom = cylinder_caps(&cap, ray, t_min, t_max, obj_cont(obj)->cy.radius);
	t_min_cy = t_cap_bottom;
	cap.pl.pos = vec3_linear_comb(1.0, obj_cont(obj)->cy.pos, obj_cont(obj)->cy.height, obj_cont(obj)->cy.dir);
	cap.pl.dir = obj_cont(obj)->cy.dir;
	t_cap_top = cylinder_caps(&cap, ray, t_min, t_max, obj_cont(obj)->cy.radius);
	if (t_cap_top > 0.0 && (t_cap_top < t_min_cy || t_min_cy == -1))
		t_min_cy = t_cap_top;
	t_lateral = cylinder_lateral(obj, ray, t_min, t_max);
	if (t_lateral > 0.0 && (t_lateral < t_min_cy || t_min_cy == -1))
		t_min_cy = t_lateral;
	return (t_min_cy);
}

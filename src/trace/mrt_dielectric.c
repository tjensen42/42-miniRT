#include "mrt_trace.h"

static double	reflectance(double cos_theta, double brechung);
static t_vec3	refract(t_list *obj, t_ray *ray, t_hit *hit, double brechung);

t_vec3	dielectric(t_list *obj, t_ray *ray, t_hit *hit)
{
	if (hit->side == OUTSIDE)
		return (refract(obj, ray, hit, 1.0 / obj_cont(obj)->material.refraction_index));
	else
	{
		hit->normal = vec3_scale(-1.0, hit->normal);
		return (refract(obj, ray, hit, obj_cont(obj)->material.refraction_index));
	}
}

static double reflectance(double cos_theta, double brechung)
{
	double r0 = (1 - brechung) / (1 + brechung);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cos_theta), 5));
}

static t_vec3	refract(t_list *obj, t_ray *ray, t_hit *hit, double brechung)
{
    double	cos_theta;
	bool	cannot_refract;

	cos_theta = fmin(vec3_scalar_product(vec3_scale(-1.0, ray->dir), hit->normal), 1.0);
	cannot_refract = (brechung * sqrt(1.0 - cos_theta*cos_theta) > 1.0);
	if (cannot_refract || reflectance(cos_theta, brechung) > (rand() / (RAND_MAX + 1.0)))
		return (specular(obj, ray, hit));
	else
	{
		t_vec3	r_out_perp = vec3_scale(brechung, vec3_add(ray->dir, vec3_scale(cos_theta, hit->normal)));
		t_vec3	r_out_parallel = vec3_scale(-sqrt(fabs(1.0 - vec3_scalar_product(r_out_perp, r_out_perp))), hit->normal);
		return (vec3_normalize(vec3_add(r_out_perp, r_out_parallel)));
	}
}

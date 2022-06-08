#include "mrt_trace.h"

static double	reflectance(double cos_theta, double ref_ratio);
static t_vec3	refract(t_list *obj, t_ray *ray, t_hit *hit, double ref_ratio);

t_vec3	dielectric(t_list *obj, t_ray *ray, t_hit *hit)
{
	double	ref_ratio;

	if (hit->side == OUTSIDE)
		ref_ratio = 1.0 / obj_material(obj)->refraction_index;
	else
		ref_ratio = obj_material(obj)->refraction_index;
	return (refract(obj, ray, hit, ref_ratio));
}

static double	reflectance(double cos_theta, double ref_ratio)
{
	double	r;

	r = (1.0 - ref_ratio) / (1.0 + ref_ratio);
	r = r * r;
	return (r + (1.0 - r) * pow((1.0 - cos_theta), 5.0));
}

static t_vec3	refract(t_list *obj, t_ray *ray, t_hit *hit, double ref_ratio)
{
	t_vec3	normal;
	t_vec3	r_out_perp;
	t_vec3	r_out_para;
	double	cos_theta;
	bool	cannot_refract;

	if (hit->side == OUTSIDE)
		normal = hit->normal;
	else
		normal = vec3_scale(-1.0, hit->normal);
	cos_theta = fmin(vec3_dot(vec3_scale(-1.0, ray->dir), normal), 1.0);
	cannot_refract = (ref_ratio * sqrt(1.0 - cos_theta * cos_theta) > 1.0);
	if (cannot_refract
		|| reflectance(cos_theta, ref_ratio) > ft_rand())
		return (specular(obj, ray, hit));
	else
	{
		r_out_perp = vec3_scale(ref_ratio,
				vec3_add(ray->dir, vec3_scale(cos_theta, normal)));
		r_out_para = vec3_scale(
				-sqrt(fabs(1.0 - vec3_dot(r_out_perp, r_out_perp))), normal);
		return (vec3_norm(vec3_add(r_out_perp, r_out_para)));
	}
}

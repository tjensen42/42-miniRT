#include "mrt_trace.h"

double pdf_sphere(t_scene *scene __attribute__((unused)), t_list *is, t_hit *hit)
{
	double	cos_theta_max;
	double	solid_angle;
	t_ray	ray;
	t_vec3	is_dir;

	is_dir = vec3_subtract(is_cont(is)->pos, hit->p);
	ray.pos = hit->p;
	ray.dir = vec3_normalize(is_dir);
	// if (calc_hit(scene->l_obj, &ray, &rec) == NULL)
	// 	return (0);
	cos_theta_max = sqrt(1 - is_cont(is)->radius * is_cont(is)->radius / vec3_scalar_product(is_dir, is_dir));
	solid_angle = 2 * M_PI * (1 - cos_theta_max);
    return  (1 / solid_angle);
}

#include "mrt_trace.h"

double	pdf_sphere(t_scene *scene __attribute__((unused)), t_list *light, t_hit *hit)
{
	double	cos_theta_max;
	double	solid_angle;
	t_ray	ray;
	t_vec3	light_dir;

	light_dir = vec3_subtract(light_cont(light)->linked_c_obj->sp.pos, hit->p);
	ray.pos = hit->p;
	ray.dir = vec3_normalize(light_dir);
	// if (calc_hit(scene->l_obj, &ray, &rec) == NULL)
	// 	return (0);
	cos_theta_max = sqrt(1 - light_cont(light)->linked_c_obj->sp.radius * light_cont(light)->linked_c_obj->sp.radius / vec3_scalar_product(light_dir, light_dir));
	solid_angle = 2 * M_PI * (1 - cos_theta_max);
    return  (1 / solid_angle);
}

double	pdf_disc(t_scene *scene __attribute__((unused)), t_list *light, t_hit *hit)
{
	double	cosine;
	double	length_squared;
	t_vec3	light_dir;
	t_obj	*c_obj;

	c_obj = light_cont(light)->linked_c_obj;
	light_dir = vec3_subtract(c_obj->di.pos, hit->p);
	length_squared = vec3_scalar_product(light_dir, light_dir);
	light_dir = vec3_normalize(light_dir);
	cosine = fabs(vec3_scalar_product(light_dir, c_obj->di.dir));
	return (length_squared / (cosine * M_PI * c_obj->di.radius * c_obj->di.radius));
}

double	pdf_rectangle(t_scene *scene __attribute__((unused)), t_list *light, t_hit *hit)
{
	double	cosine;
	double	length_squared;
	t_vec3	light_dir;
	t_obj	*c_obj;

	c_obj = light_cont(light)->linked_c_obj;
	light_dir = vec3_subtract(c_obj->rt.pos, hit->p);
	length_squared = vec3_scalar_product(light_dir, light_dir);
	light_dir = vec3_normalize(light_dir);
	cosine = fabs(vec3_scalar_product(light_dir, c_obj->rt.dir));
	return (length_squared / (cosine * c_obj->rt.width * c_obj->rt.height));
}

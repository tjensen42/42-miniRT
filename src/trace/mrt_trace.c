#include "mrt_trace.h"

# include <float.h>

t_list	*calc_hit(t_list *l_obj, t_ray *ray, t_hit *hit);

t_color	trace(t_scene *scene, t_ray *ray, int depth)
{
	t_list	*hit_obj;
	t_hit	hit;
	t_color	color;
	t_ray	ray_recursion;

	if (depth == scene->sampling.recursion_depth)
		return ((t_color){0.0, 0.0, 0.0});
	hit_obj = calc_hit(scene->l_obj, ray, &hit);
	if (hit_obj)
	{
		ray_recursion.pos = hit.p;
		double rand_double = ft_rand_double_0_1();

		if (rand_double < obj_cont(hit_obj)->material.surface[SURF_DIFFUSE])
			ray_recursion.dir = diffuse(hit_obj, ray, &hit);
		else if (rand_double < obj_cont(hit_obj)->material.surface[SURF_DIFFUSE] + obj_cont(hit_obj)->material.surface[SURF_SPECULAR])
		{
			ray_recursion.dir = specular(hit_obj, ray, &hit);
			if (ray_recursion.dir.x == 0.0 && ray_recursion.dir.y == 0.0 && ray_recursion.dir.z == 0.0)
				return ((t_color){0.0, 0.0, 0.0});
		}
		else if (rand_double < obj_cont(hit_obj)->material.surface[SURF_DIFFUSE] + obj_cont(hit_obj)->material.surface[SURF_SPECULAR] + obj_cont(hit_obj)->material.surface[SURF_DIELECTRIC])
			ray_recursion.dir = dielectric(hit_obj, ray, &hit);
		else
			return (color_scale(20.0, obj_cont(hit_obj)->material.color));
		color = trace(scene, &ray_recursion, depth + 1);
		return (color_multiply(obj_cont(hit_obj)->material.color, color));
	}
	else
		return (color_blend(0.5 * (ray->dir.y + 1), scene->bg.color[1], scene->bg.color[0]));
}

t_list	*calc_hit(t_list *l_obj, t_ray *ray, t_hit *hit)
{
	double	t;
	t_list	*obj;

	obj = NULL;
	hit->t = -1.0;
	while (l_obj)
	{
		t = obj_cont(l_obj)->intersec(l_obj, ray, 0.001, DBL_MAX);
		if (t > 0 && (t < hit->t || hit->t == -1.0)) // >= ??
		{
			obj = l_obj;
			hit->t = t;
		}
		l_obj = l_obj->next;
	}
	if (obj)
	{
		hit->p = vec3_linear_comb(1.0, ray->pos, hit->t, ray->dir);
		hit->normal = obj_cont(obj)->normal(obj, hit);
		if (vec3_scalar_product(hit->normal, ray->dir) > 0.0)
			hit->side = INSIDE;
		else
			hit->side = OUTSIDE;
	}
	return (obj);
}

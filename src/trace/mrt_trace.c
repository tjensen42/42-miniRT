#include "mrt_trace.h"

#include <float.h>

double mixed_sampling_pdf(t_scene *scene, t_ray *ray, t_hit *hit)
{
	double	cosine;
	double	cosine_pdf;
	double	import_pdf;
	double	mixed_pdf;
	t_list	*iter;

	cosine = vec3_scalar_product(hit->normal, ray->dir);
	if ((cosine < 0 && hit->side == OUTSIDE) || (cosine > 0 && hit->side == INSIDE))
		return (0);
	else
		cosine_pdf = fabs(cosine / M_PI);
	import_pdf = 0;
	iter = scene->l_is;
	while (iter)
	{
		import_pdf += is_cont(iter)->weight * is_cont(iter)->pdf_value(scene, iter, hit);
		iter = iter->next;
	}
	mixed_pdf = scene->sampling.cosine_samp * cosine_pdf + scene->sampling.import_samp * import_pdf;
	return (mixed_pdf);
}

t_vec3	random_dir_import_sampling(t_list *l_is, t_hit *hit)
{
	double	random;
	double	weight_sum;

	weight_sum = 0;
	random = ft_rand_double_0_1();
	while (l_is)
	{
		weight_sum += is_cont(l_is)->weight;
		if (random <= weight_sum)
		{
			return (is_cont(l_is)->random_dir(l_is, hit));
		}
		l_is = l_is->next;
	}
}

t_color	trace(t_scene *scene, t_ray *ray, int depth)
{
	t_list	*hit_obj;
	t_hit	hit;
	t_color	color;
	t_ray	ray_recursion;
	double	rand_double;
	double	scattering_pdf;

	if (depth == scene->sampling.recursion_depth)
		return ((t_color){0.0, 0.0, 0.0});
	hit_obj = calc_hit(scene->l_obj, ray, &hit);
	if (hit_obj)
	{
		ray_recursion.pos = hit.p;
		rand_double = ft_rand_double_0_1();

		if (rand_double < obj_cont(hit_obj)->material.surface[SURF_DIFFUSE])
		{
			// ray_recursion.dir = diffuse(hit_obj, ray, &hit);
			rand_double = ft_rand_double_0_1();
			if (rand_double < scene->sampling.import_samp)
			{
				ray_recursion.dir = random_dir_import_sampling(scene->l_is, &hit);
				// if (vec3_scalar_product(ray_recursion.dir, hit.normal) < 0)
				// 	return ((t_color){0.0, 0.0, 1.0});
			}
			else
			{
				if (hit.side == INSIDE)
					ray_recursion.dir = random_cosine_direction_onb(vec3_scale(-1.0, hit.normal));
				else
					ray_recursion.dir = random_cosine_direction_onb(hit.normal);
				// if (calc_hit(scene->l_obj, &ray_recursion, &hit2) == NULL)
				// 	return (color_multiply(obj_cont(hit_obj)->material.color, color_blend(0.5 * (ray->dir.y + 1), scene->bg.color[1], scene->bg.color[0]))); // color add
			}
			double mixed_sampling_pdf_value = mixed_sampling_pdf(scene, &ray_recursion, &hit);
			if (mixed_sampling_pdf_value == 0)
				return ((t_color){0.0, 0.0, 0.0});
			double cosine = vec3_scalar_product(hit.normal, ray_recursion.dir);
			if ((cosine < 0 && hit.side == OUTSIDE) || (cosine > 0 && hit.side == INSIDE))
				scattering_pdf = 0;
			else
				scattering_pdf = fabs(cosine / M_PI);
			color = trace(scene, &ray_recursion, depth + 1);
			return (color_multiply(obj_cont(hit_obj)->material.color, color_scale(scattering_pdf / mixed_sampling_pdf_value, color)));
		}
		else if (rand_double < obj_cont(hit_obj)->material.surface[SURF_DIFFUSE] + obj_cont(hit_obj)->material.surface[SURF_SPECULAR])
		{
			ray_recursion.dir = specular(hit_obj, ray, &hit);
			if (ray_recursion.dir.x == 0.0 && ray_recursion.dir.y == 0.0 && ray_recursion.dir.z == 0.0)
				return ((t_color){0.0, 0.0, 0.0});
		}
		else if (rand_double < obj_cont(hit_obj)->material.surface[SURF_DIFFUSE] + obj_cont(hit_obj)->material.surface[SURF_SPECULAR] + obj_cont(hit_obj)->material.surface[SURF_DIELECTRIC])
			ray_recursion.dir = dielectric(hit_obj, ray, &hit);
		else
			return (color_scale(obj_cont(hit_obj)->material.brightness, obj_cont(hit_obj)->material.color));
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

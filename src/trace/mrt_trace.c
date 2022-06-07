#include "mrt_trace.h"

#include <float.h>

// t_color	trace(t_scene *scene, t_ray *ray, int depth)
// {
// 	t_list	*hit_obj;
// 	t_hit	hit;
// 	t_color	color;
// 	t_ray	ray_recursion;
// 	double	rand_double;
// 	double	scattering_pdf;

// 	if (depth == scene->sampling.recursion_depth)
// 		return ((t_color){0.0, 0.0, 0.0});
// 	hit_obj = calc_hit(scene->l_obj, ray, &hit);
// 	if (hit_obj)
// 	{
// 		ray_recursion.pos = hit.p;
// 		rand_double = ft_rand_double_0_1();

// 		if (rand_double < obj_cont(hit_obj)->material.surface[DIFFUSE])
// 		{
// 			rand_double = ft_rand_double_0_1();
// 			if (scene->l_light && rand_double < scene->sampling.import_samp)
// 				ray_recursion.dir = diffuse_light_sampling(scene->l_light, &hit);
// 			else
// 			{
// 				if (hit.side == INSIDE)
// 					ray_recursion.dir = random_cosine_direction_onb(vec3_scale(-1.0, hit.normal));
// 				else
// 					ray_recursion.dir = random_cosine_direction_onb(hit.normal);
// 			}
// 			double mixed_sampling_pdf_value = mixed_sampling_pdf(scene, &ray_recursion, &hit);
// 			if (mixed_sampling_pdf_value == 0)
// 				return ((t_color){0.0, 0.0, 0.0});
// 			double cosine = vec3_scalar_product(hit.normal, ray_recursion.dir);
// 			if ((cosine < 0 && hit.side == OUTSIDE) || (cosine > 0 && hit.side == INSIDE))
// 				scattering_pdf = 0;
// 			else
// 				scattering_pdf = fabs(cosine / M_PI);
// 			color = trace(scene, &ray_recursion, depth + 1);
// 			if (depth == 0)
// 				return (color_max(color_multiply(obj_cont(hit_obj)->material.get_color(hit_obj, &hit), color_scale(scattering_pdf / mixed_sampling_pdf_value, color)), scene->amb.color));
// 			else
// 				return (color_multiply(obj_cont(hit_obj)->material.get_color(hit_obj, &hit), color_scale(scattering_pdf / mixed_sampling_pdf_value, color)));
// 		}


// 		else if (rand_double < obj_material(hit_obj)->surface[DIFFUSE] + obj_material(hit_obj)->surface[SPECULAR])
// 		{
// 			ray_recursion.dir = specular(hit_obj, ray, &hit);
// 			if (ray_recursion.dir.x == 0.0 && ray_recursion.dir.y == 0.0 && ray_recursion.dir.z == 0.0)
// 				return ((t_color){0.0, 0.0, 0.0});
// 		}


// 		else if (rand_double < obj_material(hit_obj)->surface[DIFFUSE] + obj_material(hit_obj)->surface[SPECULAR] + obj_material(hit_obj)->surface[DIELECTRIC])
// 			ray_recursion.dir = dielectric(hit_obj, ray, &hit);


// 		else
// 		{
// 			if (hit.side == INSIDE)
// 				return ((t_color){0.0, 0.0, 0.0});
// 			else
// 				return (color_scale(obj_cont(hit_obj)->material.brightness, obj_cont(hit_obj)->material.get_color(hit_obj, &hit)));
// 		}
// 		color = trace(scene, &ray_recursion, depth + 1);
// 		return (color_multiply(obj_cont(hit_obj)->material.get_color(hit_obj, &hit), color));
// 	}
// 	else
// 		return (color_blend(0.5 * (ray->dir.y + 1), scene->bg.color[1], scene->bg.color[0]));
// }












t_color	trace_bg_color(struct s_bg *bg, t_ray *ray);
t_color	trace_obj_color(t_list *obj, t_ray *ray, t_hit *hit, t_scene *scene, int depth);
int	surface_select(double surface[4], double light_sampling);
t_color	emission(t_list *obj, t_hit *hit);

t_color	trace(t_scene *scene, t_ray *ray, int depth)
{
	t_list	*hit_obj;
	t_hit	hit;
	t_ray	ray_rec;
	int		surface;
	t_color	trace_color;
	double	scaling;

	if (depth == scene->sampling.recursion_depth)
		return ((t_color){0.0, 0.0, 0.0});
	hit_obj = calc_hit(scene->l_obj, ray, &hit);
	if (hit_obj == NULL)
		return (trace_bg_color(&(scene->bg), ray));
	scaling = 1.0;
	ray_rec.pos = hit.p;
	surface = surface_select(obj_material(hit_obj)->surface, scene->sampling.light);
	if (surface == DIFFUSE_LIGHT)
		ray_rec.dir = diffuse_light_sampling(scene->l_light, &hit);
	if (surface == DIFFUSE_COSINE)
		ray_rec.dir = diffuse_cosine_sampling(&hit);
	if (surface == SPECULAR)
		ray_rec.dir = specular(hit_obj, ray, &hit);
	else if (surface == DIELECTRIC)
		ray_rec.dir = dielectric(hit_obj, ray, &hit);
	else if (surface == EMISSION)
		return (emission(hit_obj, &hit));
	if (vec3_equal((t_vec3){0.0, 0.0, 0.0}, ray_rec.dir))
		return ((t_color){0.0, 0.0, 0.0});
	if (surface == DIFFUSE_LIGHT || surface == DIFFUSE_COSINE)
		scaling = get_scaling(scene, &ray_rec, &hit);
	trace_color = trace(scene, &ray_rec, depth + 1);
	trace_color = color_scale(scaling, trace_color);
	return (color_max(color_multiply(obj_material(hit_obj)->get_color(hit_obj, &hit), trace_color), scene->amb.color));
	// amb all
}

// t_color	trace_obj_color(t_list *obj, t_ray *ray, t_hit *hit, t_scene *scene, int depth)
// {

// }

t_color	emission(t_list *obj, t_hit *hit)
{
	if (hit->side == INSIDE)
		return ((t_color){0.0, 0.0, 0.0});
	else
		return (color_scale(obj_material(obj)->brightness,
								obj_material(obj)->get_color(obj, hit)));
}

int	surface_select(double surface[4], double light_sampling)
{
	double	random;

	random = ft_rand_double_0_1();
	if (random < surface[DIFFUSE])
	{
		random = ft_rand_double_0_1();
		if (random < light_sampling)
			return (DIFFUSE_LIGHT);
		return (DIFFUSE_COSINE);
	}
	else if (random < surface[DIFFUSE] + surface[SPECULAR])
		return (SPECULAR);
	else if (random < surface[DIFFUSE] + surface[SPECULAR]
			+ surface[DIELECTRIC])
		return (DIELECTRIC);
	else
		return (EMISSION);
}

inline t_color	trace_bg_color(struct s_bg *bg, t_ray *ray)
{
	return (color_blend(0.5 * (ray->dir.y + 1), bg->color[1], bg->color[0]));
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

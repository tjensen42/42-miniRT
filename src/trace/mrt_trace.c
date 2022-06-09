/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:55:11 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:55:11 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_trace.h"

#include <float.h>

static t_color	emission(t_list *obj, t_hit *hit);
static t_list	*calc_hit(t_list *l_obj, t_ray *ray, t_hit *hit);
static t_ray	new_ray(t_scene *scene, t_ray *ray, t_hit *hit, double *scale);
static int		surface_select(double surface[4], double light_sampling);

t_color	trace(t_scene *scene, t_ray *ray, int depth)
{
	t_hit	hit;
	t_ray	ray_rec;
	t_color	trace_color;
	double	scale;

	if (depth == scene->sampling.recursion_depth)
		return ((t_color){0.0, 0.0, 0.0});
	if (calc_hit(scene->l_obj, ray, &hit) == NULL)
		return (color_blend(0.5 * (ray->dir.y + 1),
				scene->bg.color[1], scene->bg.color[0]));
	if (obj_material(hit.obj)->surface[EMISSION] == 1.0)
		return (emission(hit.obj, &hit));
	ray_rec = new_ray(scene, ray, &hit, &scale);
	if (vec3_equal((t_vec3){0.0, 0.0, 0.0}, ray_rec.dir))
		return (scene->amb.color);
	trace_color = trace(scene, &ray_rec, depth + 1);
	trace_color = color_scale(scale, trace_color);
	trace_color = color_multi(
			obj_material(hit.obj)->get_color(hit.obj, &hit), trace_color);
	if (depth == 0)
		return (color_add(trace_color, scene->amb.color));
	return (trace_color);
}

static t_color	emission(t_list *obj, t_hit *hit)
{
	if (hit->side == INSIDE)
		return ((t_color){0.0, 0.0, 0.0});
	else
		return (color_scale(obj_material(obj)->brightness,
				obj_material(obj)->get_color(obj, hit)));
}

static t_list	*calc_hit(t_list *l_obj, t_ray *ray, t_hit *hit)
{
	double	t;

	hit->obj = NULL;
	hit->t = -1.0;
	while (l_obj)
	{
		t = obj_cont(l_obj)->intersect(l_obj, ray, 0.001, DBL_MAX);
		if (t > 0 && (t < hit->t || hit->t == -1.0))
		{
			hit->obj = l_obj;
			hit->t = t;
		}
		l_obj = l_obj->next;
	}
	if (hit->obj)
	{
		hit->p = vec3_lin_comb(1.0, ray->pos, hit->t, ray->dir);
		hit->normal = obj_cont(hit->obj)->normal(hit->obj, hit);
		if (vec3_dot(hit->normal, ray->dir) > 0.0)
			hit->side = INSIDE;
		else
			hit->side = OUTSIDE;
	}
	return (hit->obj);
}

static t_ray	new_ray(t_scene *scene, t_ray *ray, t_hit *hit, double *scale)
{
	t_ray	new_ray;
	int		surface;

	new_ray.pos = hit->p;
	surface = surface_select(obj_material(hit->obj)->surface,
			scene->sampling.light);
	if (surface == DIFFUSE_LIGHT)
		new_ray.dir = diffuse_light_sampling(scene->l_light, hit);
	else if (surface == DIFFUSE_COSINE)
		new_ray.dir = diffuse_cosine_sampling(hit);
	else if (surface == SPECULAR)
		new_ray.dir = specular(hit->obj, ray, hit);
	else if (surface == DIELECTRIC)
		new_ray.dir = dielectric(hit->obj, ray, hit);
	if (surface == DIFFUSE_LIGHT || surface == DIFFUSE_COSINE)
		*scale = pdf_scaling(scene, &new_ray, hit);
	else
		*scale = 1.0;
	return (new_ray);
}

static int	surface_select(double surface[4], double light_sampling)
{
	double	random;

	random = ft_rand();
	if (random < surface[DIFFUSE])
	{
		random = ft_rand();
		if (random < light_sampling)
			return (DIFFUSE_LIGHT);
		return (DIFFUSE_COSINE);
	}
	else if (random < surface[DIFFUSE] + surface[SPECULAR])
		return (SPECULAR);
	else
		return (DIELECTRIC);
}

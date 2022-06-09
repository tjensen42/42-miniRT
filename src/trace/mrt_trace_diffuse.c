/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_trace_diffuse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:54:54 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:54:54 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_trace.h"

static double	mixed_sampling_pdf(t_scene *scene, t_ray *ray, t_hit *hit);

t_vec3	diffuse_light_sampling(t_list *l_light, t_hit *hit)
{
	double	random;
	double	weight_sum;

	weight_sum = 0;
	random = ft_rand();
	while (l_light)
	{
		weight_sum += light_cont(l_light)->weight;
		if (random <= weight_sum)
			return (light_cont(l_light)->random_dir(l_light, hit));
		l_light = l_light->next;
	}
	return (hit->normal);
}

t_vec3	diffuse_cosine_sampling(t_hit *hit)
{
	if (hit->side == INSIDE)
		return (random_cosine_direction_onb(vec3_scale(-1.0, hit->normal)));
	else
		return (random_cosine_direction_onb(hit->normal));
}

double	pdf_scaling(t_scene *scene, t_ray *ray, t_hit *hit)
{
	double	cosine;
	double	mixed_sampling_pdf_value;
	double	scattering_pdf;

	mixed_sampling_pdf_value = mixed_sampling_pdf(scene, ray, hit);
	if (mixed_sampling_pdf_value == 0.0)
		return (0.0);
	cosine = vec3_dot(hit->normal, ray->dir);
	if ((cosine < 0 && hit->side == OUTSIDE)
		|| (cosine > 0 && hit->side == INSIDE))
		scattering_pdf = 0;
	else
		scattering_pdf = fabs(cosine / M_PI);
	return (scattering_pdf / mixed_sampling_pdf_value);
}

static double	mixed_sampling_pdf(t_scene *scene, t_ray *ray, t_hit *hit)
{
	t_list	*iter;
	double	cosine;
	double	cosine_pdf;
	double	import_pdf;

	cosine = vec3_dot(hit->normal, ray->dir);
	if ((cosine < 0.0 && hit->side == OUTSIDE)
		|| (cosine > 0.0 && hit->side == INSIDE))
		return (0.0);
	else
		cosine_pdf = fabs(cosine / M_PI);
	if (scene->l_light == NULL)
		return (cosine_pdf);
	import_pdf = 0.0;
	iter = scene->l_light;
	while (iter)
	{
		import_pdf += light_cont(iter)->weight
			* light_cont(iter)->pdf_value(iter, hit);
		iter = iter->next;
	}
	return (scene->sampling.cosine * cosine_pdf
		+ scene->sampling.light * import_pdf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_trace_specular.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:55:12 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:55:13 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_trace.h"

t_vec3	specular(t_list *obj, t_ray *ray, t_hit *hit)
{
	t_vec3	dir;

	if (obj_cont(obj)->material.fuzz == 0.0)
		return (vec3_norm(vec3_add(ray->dir, vec3_scale(-2.0
						* vec3_dot(ray->dir, hit->normal), hit->normal))));
	dir = vec3_add(ray->dir, vec3_add(vec3_scale(-2.0
					* vec3_dot(ray->dir, hit->normal), hit->normal),
				vec3_scale(obj_material(obj)->fuzz, random_in_unit_sphere())));
	if (hit->side == OUTSIDE && vec3_dot(dir, hit->normal) <= 0.0)
		return ((t_vec3){0.0, 0.0, 0.0});
	else if (hit->side == INSIDE && vec3_dot(dir, hit->normal) >= 0.0)
		return ((t_vec3){0.0, 0.0, 0.0});
	return (vec3_norm(dir));
}

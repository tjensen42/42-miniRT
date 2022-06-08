/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_math_vec3_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:30:37 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/08 11:50:08 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math.h"

bool	vec3_equal(t_vec3 a, t_vec3 b)
{
	return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
}

double	vec3_len(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double	vec3_dist(t_vec3 a, t_vec3 b)
{
	return (vec3_len(vec3_sub(a, b)));
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

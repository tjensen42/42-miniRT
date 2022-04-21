/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_math_vec3_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:31:25 by tjensen           #+#    #+#             */
/*   Updated: 2022/04/21 13:22:17 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	vec3_subtract(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3_scale(double alpha, t_vec3 a)
{
	return ((t_vec3){alpha * a.x, alpha * a.y, alpha * a.z});
}

t_vec3	vec3_linear_comb(double alpha, t_vec3 a, double beta, t_vec3 b)
{
	return (vec3_add(vec3_scale(alpha, a), vec3_scale(beta, b)));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	alpha;

	alpha = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return ((t_vec3){alpha * a.x, alpha * a.y, alpha * a.z});
}

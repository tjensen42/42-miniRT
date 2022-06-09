/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:49 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 13:19:14 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_MATH_H
# define MRT_MATH_H

# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_scene.h"

# include <math.h>

t_color	color_add(t_color c1, t_color c2);
t_color	color_scale(double f, t_color c1);
t_color	color_multi(t_color c1, t_color c2);

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(double alpha, t_vec3 a);
t_vec3	vec3_lin_comb(double alpha, t_vec3 a, double beta, t_vec3 b);
t_vec3	vec3_norm(t_vec3 a);

bool	vec3_equal(t_vec3 a, t_vec3 b);
double	vec3_len(t_vec3 a);
double	vec3_dist(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

#endif // MRT_MATH_H

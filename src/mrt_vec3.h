/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_vec3.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:27:56 by tjensen           #+#    #+#             */
/*   Updated: 2022/12/19 12:42:53 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_VEC3_H
# define MRT_VEC3_H

# include "libft/inc/libft.h"

# include <stdbool.h>

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// VEC3_PARSE
int		parse_vec3(const char *str, t_vec3 *vec3);

// VEC3_PRINT
void	print_vec3(t_vec3 vec3, const char *str, const char *color);

// VEC3_MATH_1
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(double alpha, t_vec3 a);
t_vec3	vec3_lin_comb(double alpha, t_vec3 a, double beta, t_vec3 b);
t_vec3	vec3_norm(t_vec3 a);

// VEC3_MATH_2
bool	vec3_equal(t_vec3 a, t_vec3 b);
double	vec3_len(t_vec3 a);
double	vec3_dist(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

#endif // MRT_VEC3_H

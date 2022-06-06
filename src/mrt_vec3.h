/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_vec3.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:27:56 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/06 17:37:16 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_VEC3_H
# define MRT_VEC3_H

# include "lib/libft/inc/libft.h"

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
t_vec3	vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(double alpha, t_vec3 a);
t_vec3	vec3_linear_comb(double alpha, t_vec3 a, double beta, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 a);

// VEC3_MATH_2
bool	vec3_equal(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 a);
double	vec3_distance(t_vec3 a, t_vec3 b);
double	vec3_scalar_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_vector_product(t_vec3 a, t_vec3 b);

#endif // MRT_VEC3_H

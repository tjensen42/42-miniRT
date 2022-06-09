/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:32:01 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:17:35 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_COLOR_H
# define MRT_COLOR_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <stdbool.h>

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define COLOR_NO		"\033[m"
# define COLOR_RE		"\033[0;31m"
# define COLOR_RE_1		"\033[1;31m"
# define COLOR_YE		"\033[0;33m"
# define COLOR_YE_1		"\033[1;33m"
# define COLOR_GR		"\033[0;32m"
# define COLOR_GR_1		"\033[1;32m"
# define COLOR_BL		"\033[0;34m"
# define COLOR_BL_1		"\033[1;34m"
# define COLOR_PL		"\033[0;35m"
# define COLOR_PL_1		"\033[1;35m"
# define COLOR_CY		"\033[0;36m"
# define COLOR_CY_1		"\033[1;36m"

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// COLOR_UTILS
double	color_clamp(double color, double min, double max);
t_color	color_blend(double f, t_color c1, t_color c2);
t_color	color_gamma_encode(t_color color);
int		color_to_rgba_int(t_color color, bool gamma_correction);
t_color	color_max(t_color c1, t_color c2);

#endif // MRT_COLOR_H

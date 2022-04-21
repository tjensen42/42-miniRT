/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:12:06 by tjensen           #+#    #+#             */
/*   Updated: 2022/04/21 10:39:08 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_color.h"

#include <math.h>

inline double	color_clamp(double color, double min, double max)
{
	if (color < min)
		return (min);
	if (color > max)
		return (max);
	return (color);
}

inline t_color	color_blend(double f, t_color c1, t_color c2)
{
	return ((t_color){
		(1.0 - f) * c1.r + f * c2.r,
		(1.0 - f) * c1.g + f * c2.g,
		(1.0 - f) * c1.b + f * c2.b
	});
}

inline t_color	color_gamma_encode(t_color color)
{
	return ((t_color){sqrt(color.r), sqrt(color.g), sqrt(color.b)});
}

inline int	color_to_rgba_int(t_color color)
{
	if (color.r != color.r)
		color.r = 0;
	if (color.g != color.g)
		color.g = 0;
	if (color.b != color.b)
		color.b = 0;
	color = color_gamma_encode(color);
	return (
		(int)(256.0 * color_clamp(color.r, 0.0, 0.999)) << 24 |
		(int)(256.0 * color_clamp(color.g, 0.0, 0.999)) << 16 |
		(int)(256.0 * color_clamp(color.b, 0.0, 0.999)) << 8  |
		(int)(0xFF)
			);
}

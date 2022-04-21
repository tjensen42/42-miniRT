/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_math_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:11:53 by tjensen           #+#    #+#             */
/*   Updated: 2022/04/20 15:46:53 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math.h"

inline t_color	color_add(t_color c1, t_color c2)
{
	return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

inline t_color	color_scale(double f, t_color c1)
{
	return ((t_color){f * c1.r, f * c1.g, f * c1.b});
}

inline t_color	color_multiply(t_color c1, t_color c2)
{
	return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

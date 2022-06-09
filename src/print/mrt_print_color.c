/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_print_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:57:32 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:57:32 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_print.h"

inline void	print_color(t_color color)
{
	printf("\t%-10s %s%8d %s%8d %s%8d%s\n",
		"color:",
		COLOR_RE, (int)(256 * color_clamp(color.r, 0.0, 0.999)),
		COLOR_GR, (int)(256 * color_clamp(color.g, 0.0, 0.999)),
		COLOR_BL, (int)(256 * color_clamp(color.b, 0.0, 0.999)),
		"\033[m");
}

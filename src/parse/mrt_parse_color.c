/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:52 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 17:44:13 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"

int	parse_color(const char *str, t_color *color)
{
	char	**split;
	int		primary;
	int		error;

	split = ft_split(str, ',');
	if (split == NULL)
		return (-1);
	primary = 0;
	error = (ft_split_count_str(split) != 3);
	if (!error)
		error = int_from_str(split[0], 0, 255, &primary);
	(*color).r = (double)primary / 255.0;
	if (!error)
		error = int_from_str(split[1], 0, 255, &primary);
	(*color).g = (double)primary / 255.0;
	if (!error)
		error = int_from_str(split[2], 0, 255, &primary);
	(*color).b = (double)primary / 255.0;
	ft_free_split(&split);
	return (error);
}

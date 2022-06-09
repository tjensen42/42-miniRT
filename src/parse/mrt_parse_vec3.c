/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:19 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:56:19 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"

int	parse_vec3(const char *str, t_vec3 *vec3)
{
	char	**split;

	split = ft_split(str, ',');
	if (split == NULL)
		return (-1);
	if (ft_split_count_str(split) != 3)
	{
		ft_free_split(&split);
		return (-1);
	}
	if (double_from_str(split[0], 6, 4, &((*vec3).x)))
		return (-1);
	if (double_from_str(split[1], 6, 4, &((*vec3).y)))
		return (-1);
	if (double_from_str(split[2], 6, 4, &((*vec3).z)))
		return (-1);
	ft_free_split(&split);
	return (0);
}

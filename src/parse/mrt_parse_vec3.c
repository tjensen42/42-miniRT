/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:19 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 16:56:49 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"

int	parse_vec3(const char *str, t_vec3 *vec3)
{
	int		error;
	char	**split;

	split = ft_split(str, ',');
	if (split == NULL)
		return (-1);
	error = (ft_split_count_str(split) != 3);
	error = double_from_str(split[0], 6, 4, &((*vec3).x));
	error = double_from_str(split[1], 6, 4, &((*vec3).y));
	error = double_from_str(split[2], 6, 4, &((*vec3).z));
	ft_free_split(&split);
	return (error);
}

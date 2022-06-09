/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_res.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:29 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:56:29 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"

int	parse_res(t_scene *scene, char **split, int line_num)
{
	if (scene->img.res_set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_DUPLICATE, ID_RES));
	if (ft_split_count_str(split) != 3)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	if (int_from_str(split[1], 10, 10000, &(scene->img.width)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_RES, NULL));
	if (int_from_str(split[2], 10, 10000, &(scene->img.height)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_RES, NULL));
	scene->img.res_set = true;
	return (0);
}

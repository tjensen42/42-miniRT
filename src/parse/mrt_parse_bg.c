/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_bg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:55 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/10 09:50:22 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"

int	parse_bg(t_scene *scene, char **split, int line_num)
{
	if (scene->bg.set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_DUP_ID, ID_BG));
	if (ft_split_count_str(split) != 3)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	if (parse_color(split[1], &(scene->bg.color[0])))
		return (print_error_scene(line_num, ERR_PARSE, ERR_COLOR, NULL));
	if (parse_color(split[2], &(scene->bg.color[1])))
		return (print_error_scene(line_num, ERR_PARSE, ERR_COLOR, NULL));
	scene->bg.set = true;
	return (0);
}

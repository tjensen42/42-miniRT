/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_cam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:54 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 16:57:58 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"

int	parse_cam(t_scene *scene, char **split, int line_num)
{
	t_vec3	look_at;

	if (scene->cam.set == true)
		return (print_error_scene(line_num, ERR_PARSE, ERR_DUPLICATE, ID_CAM));
	if (ft_split_count_str(split) != 4)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	if (parse_vec3(split[1], &(scene->cam.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	scene->cam.pos_initial = scene->cam.pos;
	if (parse_vec3(split[2], &look_at))
		return (
			print_error_scene(line_num, ERR_PARSE, ERR_LOOK_AT, VEC3_RANGE));
	if (vec3_equal(scene->cam.pos, look_at))
		return (print_error_scene(line_num, ERR_PARSE, ERR_CAM_LOOK, NULL));
	scene->cam.dir = vec3_norm(vec3_sub(look_at, scene->cam.pos));
	scene->cam.dir_initial = scene->cam.dir;
	if (int_from_str(split[3], 1, 179, &(scene->cam.fov)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_FOV, NULL));
	scene->cam.set = true;
	return (0);
}

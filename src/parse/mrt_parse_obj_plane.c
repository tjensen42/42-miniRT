/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_obj_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:37 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:56:38 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_plane(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 7)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->pl.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	if (parse_vec3(split[2], &(c_obj->pl.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIR, VEC3_RANGE));
	c_obj->pl.dir = vec3_norm(c_obj->pl.dir);
	if (parse_material(&(c_obj->material), &split[3], line_num))
		return (-1);
	if (c_obj->material.surface[DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIELECTRIC, NULL));
	c_obj->print = &print_obj_plane;
	c_obj->intersect = &intersect_plane;
	c_obj->normal = &normal_plane;
	return (0);
}

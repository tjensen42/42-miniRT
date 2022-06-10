/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_obj_tube.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:30 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/10 09:34:02 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"
#include "print/mrt_print.h"

static void	parse_obj_tube_function_ptr(t_list *obj);

int	parse_obj_tube(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;

	if (ft_split_count_str(split) != 9)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	if (parse_vec3(split[1], &(obj_cont(obj)->tb.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	if (parse_vec3(split[2], &(obj_cont(obj)->tb.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIR, VEC3_RANGE));
	obj_cont(obj)->tb.dir = vec3_norm(obj_cont(obj)->tb.dir);
	if (double_from_str(split[3], 6, 4, &(obj_cont(obj)->tb.radius))
		|| obj_cont(obj)->tb.radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_RAD, NULL));
	if (double_from_str(split[4], 6, 4, &(obj_cont(obj)->tb.height))
		|| obj_cont(obj)->tb.height <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_HEIGHT, NULL));
	if (parse_material(&(obj_cont(obj)->material), &split[5], line_num))
		return (-1);
	if (obj_material(obj)->surface[DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIELECTRIC, NULL));
	parse_obj_tube_function_ptr(obj);
	return (0);
}

static void	parse_obj_tube_function_ptr(t_list *obj)
{
	obj_cont(obj)->print = &print_obj_tube;
	obj_cont(obj)->intersect = &intersect_tube;
	obj_cont(obj)->normal = &normal_tube;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_light_disc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:51 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:56:51 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

static int	parse_disc_obj(t_scene *scene, char **split, int line_num);

int	parse_light_disc(t_scene *scene, char **split, int line_num)
{
	t_list	*light;
	t_light	*c_light;

	if (ft_split_count_str(split) != 7)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	light = light_new();
	if (light == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_light), light);
	c_light = light_cont(light);
	if (parse_disc_obj(scene, split, line_num))
		return (-1);
	if (double_from_str(split[6], 4, 2, &(c_light->weight))
		|| c_light->weight <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_LIGHT_SF, NULL));
	c_light->linked_c_obj = ft_lstlast(scene->l_obj)->content;
	c_light->print = &print_light_disc;
	c_light->pdf_value = &pdf_disc;
	c_light->random_dir = &random_dir_to_disc;
	return (0);
}

static int	parse_disc_obj(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;

	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	if (parse_vec3(split[1], &(obj_cont(obj)->di.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	if (parse_vec3(split[2], &(obj_cont(obj)->di.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIR, VEC3_RANGE));
	if (double_from_str(split[3], 6, 3, &(obj_cont(obj)->di.radius))
		|| obj_cont(obj)->di.radius <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_RAD, NULL));
	if (parse_color(split[4], &(obj_cont(obj)->material.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_COLOR, NULL));
	obj_cont(obj)->material.surface[EMISSION] = 1.0;
	if (double_from_str(split[5], 4, 2, &(obj_cont(obj)->material.brightness))
		|| obj_cont(obj)->material.brightness <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_BRIGHT, NULL));
	obj_cont(obj)->print = &print_obj_disc;
	obj_cont(obj)->intersect = &intersect_disc;
	obj_cont(obj)->normal = &normal_disc;
	obj_cont(obj)->material.get_color = &obj_color;
	return (0);
}

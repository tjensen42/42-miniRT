/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_light_rectangle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:48 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/10 09:33:14 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

static int	parse_rectangle_obj(t_scene *scene, char **split, int line_num);
static void	parse_obj_rectangle_function_ptrs(t_list *obj);

int	parse_light_rectangle(t_scene *scene, char **split, int line_num)
{
	t_list	*light;
	t_light	*c_light;

	if (ft_split_count_str(split) != 8)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	light = light_new();
	if (light == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_light), light);
	c_light = light_cont(light);
	if (parse_rectangle_obj(scene, split, line_num))
		return (-1);
	if (double_from_str(split[7], 4, 2, &(c_light->weight))
		|| c_light->weight <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_LIGHT_SF, NULL));
	c_light->linked_c_obj = ft_lstlast(scene->l_obj)->content;
	c_light->print = &print_light_rectangle;
	c_light->pdf_value = &pdf_rectangle;
	c_light->random_dir = &random_dir_to_rectangle;
	return (0);
}

static int	parse_rectangle_obj(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;

	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	if (parse_vec3(split[1], &(obj_cont(obj)->rt.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	if (parse_obj_rectangle_dir(obj_cont(obj), split[2]))
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIR, NULL));
	if (double_from_str(split[3], 6, 4, &(obj_cont(obj)->rt.width))
		|| obj_cont(obj)->rt.width <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_WIDTH, NULL));
	if (double_from_str(split[4], 6, 4, &(obj_cont(obj)->rt.height))
		|| obj_cont(obj)->rt.height <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_HEIGHT, NULL));
	if (parse_color(split[5], &(obj_cont(obj)->material.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_COLOR, NULL));
	obj_material(obj)->surface[EMISSION] = 1.0;
	if (double_from_str(split[6], 4, 2, &(obj_material(obj)->brightness))
		|| obj_material(obj)->brightness <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_BRIGHT, NULL));
	parse_obj_rectangle_function_ptrs(obj);
	return (0);
}

static void	parse_obj_rectangle_function_ptrs(t_list *obj)
{
	obj_cont(obj)->print = &print_obj_rectangle;
	obj_cont(obj)->intersect = parse_obj_rt_intersect(obj_cont(obj)->rt.dir);
	obj_cont(obj)->normal = &normal_rectangle;
	obj_cont(obj)->material.get_color = &obj_color;
}

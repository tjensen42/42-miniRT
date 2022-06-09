#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

static int	parse_rectangle_obj(t_scene *scene, char **split, int line_num);

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
	t_obj	*c_obj;

	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->rt.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	if (parse_obj_rectangle_dir(c_obj, split[2]))
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIR, NULL));
	if (double_from_str(split[3], 6, 3, &(c_obj->rt.width))
		|| c_obj->rt.width <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_WIDTH, NULL));
	if (double_from_str(split[4], 6, 3, &(c_obj->rt.height))
		|| c_obj->rt.height <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_HEIGHT, NULL));
	if (parse_color(split[5], &(c_obj->material.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_COLOR, NULL));
	obj_material(obj)->surface[EMISSION] = 1.0;
	if (double_from_str(split[6], 4, 2, &(obj_material(obj)->brightness))
		|| obj_material(obj)->brightness <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_BRIGHT, NULL));
	c_obj->print = &print_obj_rectangle;
	c_obj->intersect = parse_obj_rt_intersec(c_obj->rt.dir);
	c_obj->normal = &normal_rectangle;
	c_obj->material.get_color = &obj_color;
	// c_obj->rt.rel_pos = (t_vec3){0.0, 0.0, 0.0};
	return (0);
}

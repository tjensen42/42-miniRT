#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_tube(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 9)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->tb.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(c_obj->tb.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	c_obj->tb.dir = vec3_normalize(c_obj->tb.dir);
	if (double_from_str(split[3], 6, 2, &(c_obj->tb.radius)) || c_obj->tb.radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (double_from_str(split[4], 6, 2, &(c_obj->tb.height)) || c_obj->tb.height <= 0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid height", NULL));
	if (parse_material(&(c_obj->material), &split[5], line_num))
		return (-1);
	c_obj->print = &print_obj_tube;
	c_obj->intersec = &intersec_tube;
	c_obj->normal = &normal_tube;
	return (0);
}

#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

int	parse_obj_sphere(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 7)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->pl.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (double_from_str(split[2], 6, 2, &(c_obj->sp.radius)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (parse_material(&(c_obj->material), &split[3], line_num))
		return (-1);
	c_obj->print = &print_obj_sphere;
	c_obj->intersec = &intersec_sphere;
	c_obj->normal = &normal_sphere;
	return (0);
}

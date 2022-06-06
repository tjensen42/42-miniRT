#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_disc(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 8)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->di.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(c_obj->di.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	c_obj->pl.dir = vec3_normalize(c_obj->di.dir);
	if (double_from_str(split[3], 6, 3, &(c_obj->di.radius)) || c_obj->di.radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_RAD, NULL));
	if (parse_material(&(c_obj->material), &split[4], line_num))
		return (-1);
	if (c_obj->material.surface[SURF_DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Value for DIELECTRIC must be 0.0 for 2D Objects", NULL));
	c_obj->print = &print_obj_disc;
	c_obj->intersec = &intersec_disc;
	c_obj->normal = &normal_disc;
	return (0);
}

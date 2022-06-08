#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_plane(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 7)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->pl.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(c_obj->pl.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	c_obj->pl.dir = vec3_norm(c_obj->pl.dir);
	if (parse_material(&(c_obj->material), &split[3], line_num))
		return (-1);
	if (c_obj->material.surface[DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIEL, NULL));
	c_obj->print = &print_obj_plane;
	c_obj->intersec = &intersect_plane;
	c_obj->normal = &normal_plane;
	return (0);
}

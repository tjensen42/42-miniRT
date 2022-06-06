#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_disc(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_disc	*di;

	if (ft_split_count_str(split) != 8)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	di = &(obj_cont(obj)->di);
	if (parse_vec3(split[1], &(di->pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(di->dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	di->dir = vec3_normalize(di->dir);
	if (double_from_str(split[3], 6, 3, &(di->radius)) || di->radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_RAD, NULL));
	if (parse_material(obj_material(obj), &split[4], line_num))
		return (-1);
	if (obj_material(obj)->surface[SURF_DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIEL, NULL));
	obj_cont(obj)->print = &print_obj_disc;
	obj_cont(obj)->intersec = &intersec_disc;
	obj_cont(obj)->normal = &normal_disc;
	return (0);
}

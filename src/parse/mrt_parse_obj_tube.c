#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_tube(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_tube	*tb;

	if (ft_split_count_str(split) != 9)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	tb = &(obj_cont(obj)->tb);
	if (parse_vec3(split[1], &(tb->pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	if (parse_vec3(split[2], &(tb->dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIR, VEC3_RANGE));
	tb->dir = vec3_norm(tb->dir);
	if (double_from_str(split[3], 6, 3, &(tb->radius)) || tb->radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_RAD, NULL));
	if (double_from_str(split[4], 6, 3, &(tb->height)) || tb->height <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_HEIGHT, NULL));
	if (parse_material(&(obj_cont(obj)->material), &split[5], line_num))
		return (-1);
	if (obj_material(obj)->surface[DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIELECTRIC, NULL));
	obj_cont(obj)->print = &print_obj_tube;
	obj_cont(obj)->intersect = &intersect_tube;
	obj_cont(obj)->normal = &normal_tube;
	return (0);
}

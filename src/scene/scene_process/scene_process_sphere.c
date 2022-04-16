#include "miniRT.h"
#include "../scene.h"

int process_sphere(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (split_count(split) != 7)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = object_new(OBJ_SPHERE);
	if (obj == NULL)
		return (ERROR);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = object_cont(obj);
	if (str_to_vec3(split[1], &(c_obj->pl.pos)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (str_to_double(split[2], 6, 2, &(c_obj->sp.radius)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (process_material(&(c_obj->material), &split[3], line_num))
		return (ERROR);
	c_obj->print = &print_sphere;
	return (0);
}

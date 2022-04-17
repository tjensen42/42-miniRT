#include "miniRT.h"
#include "../scene.h"

int process_plane(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (split_count(split) != 7)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = object_new(OBJ_PLANE);
	if (obj == NULL)
		return (ERROR);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = object_cont(obj);
	if (str_to_vec3(split[1], &(c_obj->pl.pos)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (str_to_vec3(split[2], &(c_obj->pl.dir)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (process_material(&(c_obj->material), &split[3], line_num))
		return (ERROR);
	if (c_obj->material.surface[SURF_DIELECTRIC] != 0.0)
		return (scene_print_error(line_num, ERR_PARSE, "Value for DIELECTRIC must be 0.0 for 2D Objects", NULL));
	c_obj->print = &print_plane;
	return (0);
}

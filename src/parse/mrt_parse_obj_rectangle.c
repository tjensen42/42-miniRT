#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_rectangle(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 10)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->rt.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_obj_rectangle_dir(c_obj, split[2]))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (double_from_str(split[3], 6, 2, &(c_obj->rt.width)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid width", NULL));
	if (double_from_str(split[4], 6, 2, &(c_obj->rt.height)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid height", NULL));
	if (parse_vec3(split[5], &(c_obj->rt.rot)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid rotation angles", NULL));
	if (parse_material(&(c_obj->material), &split[6], line_num))
		return (-1);
	if (c_obj->material.surface[SURF_DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Value for DIELECTRIC must be 0.0 for 2D Objects", NULL));
	c_obj->print = &print_obj_rectangle;
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);
	c_obj->normal = &normal_rectangle;
	c_obj->rt.rel_pos = (t_vec3){0.0, 0.0, 0.0};
	return (0);
}

int parse_obj_rectangle_dir(t_obj *c_obj, const char *dir)
{
	if (ft_strcmp(dir, "+X") == 0)
		c_obj->rt.dir = (t_vec3){1.0, 0.0, 0.0};
	else if (ft_strcmp(dir, "-X") == 0)
		c_obj->rt.dir = (t_vec3){-1.0, 0.0, 0.0};
	else if (ft_strcmp(dir, "+Y") == 0)
		c_obj->rt.dir = (t_vec3){0.0, 1.0, 0.0};
	else if (ft_strcmp(dir, "-Y") == 0)
		c_obj->rt.dir = (t_vec3){0.0, -1.0, 0.0};
	else if (ft_strcmp(dir, "+Z") == 0)
		c_obj->rt.dir = (t_vec3){0.0, 0.0, 1.0};
	else if (ft_strcmp(dir, "-Z") == 0)
		c_obj->rt.dir = (t_vec3){0.0, 0.0, -1.0};
	else
		return (-1);
	return (0);
}

f_intersec parse_obj_rectangle_intersec(t_vec3 dir)
{
	if (dir.x != 0.0)
		return (&intersec_rectangle_x);
	else if (dir.y != 0.0)
		return (&intersec_rectangle_y);
	else if (dir.z != 0.0)
		return (&intersec_rectangle_z);
	return (NULL);
}

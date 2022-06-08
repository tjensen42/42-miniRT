#include "mrt_parse.h"
#include "print/mrt_print.h"

static f_color parse_obj_rectangle_get_color_texture(t_vec3 dir);

int	parse_obj_rectangle(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 12)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->rt.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_obj_rectangle_dir(c_obj, split[2]))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (double_from_str(split[3], 6, 3, &(c_obj->rt.width)) || c_obj->rt.width <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_WIDTH, NULL));
	if (double_from_str(split[4], 6, 3, &(c_obj->rt.height)) || c_obj->rt.height <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_HEIGHT, NULL));
	if (parse_vec3(split[5], &(c_obj->rt.rot)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_ROT, NULL));
	if (parse_material(&(c_obj->material), &split[6], line_num))
		return (-1);
	if (c_obj->material.surface[DIELECTRIC] != 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIEL, NULL));
	c_obj->print = &print_obj_rectangle;
	c_obj->intersec = parse_obj_rt_intersec(c_obj->rt.dir);
	c_obj->normal = &normal_rectangle;
	c_obj->rt.rel_pos = (t_vec3){0.0, 0.0, 0.0};
	if (int_from_str(split[10], 0, 10000, &(c_obj->material.cb_factor)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid cb_factor", NULL));
	if (c_obj->material.cb_factor > 0 && vec3_equal((t_vec3){0.0, 0.0, 0.0}, c_obj->rt.rot))
		c_obj->material.get_color = &checkerboard_rectangle;
	if (ft_strcmp("-", split[11]) != 0)
	{
		c_obj->material.c_texture = parse_c_texture_find(scene->l_textures, split[11]);
		if (c_obj->material.c_texture == NULL)
			return (print_error_scene(line_num, ERR_PARSE, "cannot find texture", split[11]));
		c_obj->material.get_color = parse_obj_rectangle_get_color_texture(c_obj->rt.dir);
	}
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

f_intersec parse_obj_rt_intersec(t_vec3 dir)
{
	if (dir.x != 0.0)
		return (&intersect_rectangle_x);
	else if (dir.y != 0.0)
		return (&intersect_rectangle_y);
	else if (dir.z != 0.0)
		return (&intersect_rectangle_z);
	return (NULL);
}

static f_color parse_obj_rectangle_get_color_texture(t_vec3 dir)
{
	if (dir.x != 0.0)
		return (&texture_rectangle_x);
	else if (dir.y != 0.0)
		return (&texture_rectangle_y);
	else if (dir.z != 0.0)
		return (&texture_rectangle_z);
	return (NULL);
}

#include "mrt_parse.h"
#include "print/mrt_print.h"

static int	parse_obj_cuboid_sides(t_scene *scene, t_vec3 size, t_obj *c_template);

int	parse_obj_cuboid(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;
	t_vec3	size;

	if (ft_split_count_str(split) != 10)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->rt.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (double_from_str(split[2], 6, 2, &size.x) || size.x <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid width", NULL));
	if (double_from_str(split[3], 6, 2, &size.y) || size.y <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid height", NULL));
	if (double_from_str(split[4], 6, 2, &size.z) || size.z <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid depth", NULL));
	if (parse_vec3(split[5], &(c_obj->rt.rot)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid rotation angles", NULL));
	if (parse_material(&(c_obj->material), &split[6], line_num))
		return (-1);
	c_obj->print = &print_obj_rectangle;
	c_obj->normal = &normal_rectangle;
	if (parse_obj_cuboid_sides(scene, size, c_obj))
		return (-1);
	return (0);
}

static int	parse_obj_cuboid_sides(t_scene *scene, t_vec3 size, t_obj *c_template)
{
	t_list	*obj;
	t_obj	*c_obj;

	// obj = obj_new(0);
	// if (obj == NULL)
	// 	return (-1);
	// ft_lstadd_back(&(scene->l_obj), obj);
	// c_obj = obj_cont(obj);
	c_obj = c_template;
	c_obj->rt.dir = (t_vec3){0.0, 0.0, 1.0};
	c_obj->rt.width = size.x;
	c_obj->rt.height = size.y;
	c_obj->rt.rel_pos = (t_vec3){0.0, 0.0, size.z / 2.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);

	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	*c_obj = *c_template;
	c_obj->rt.dir = (t_vec3){0.0, 0.0, -1.0};
	c_obj->rt.width = size.x;
	c_obj->rt.height = size.y;
	c_obj->rt.rel_pos = (t_vec3){0.0, 0.0, size.z / -2.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);


	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	*c_obj = *c_template;
	c_obj->rt.dir = (t_vec3){0.0, 1.0, 0.0};
	c_obj->rt.width = size.x;
	c_obj->rt.height = size.z;
	c_obj->rt.rel_pos = (t_vec3){0.0, size.y / 2.0, 0.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);

	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	*c_obj = *c_template;
	c_obj->rt.dir = (t_vec3){0.0, -1.0, 0.0};
	c_obj->rt.width = size.x;
	c_obj->rt.height = size.z;
	c_obj->rt.rel_pos = (t_vec3){0.0, size.y / -2.0, 0.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);


	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	*c_obj = *c_template;
	c_obj->rt.dir = (t_vec3){1.0, 0.0, 0.0};
	c_obj->rt.width = size.y;
	c_obj->rt.height = size.z;
	c_obj->rt.rel_pos = (t_vec3){size.x / 2.0, 0.0, 0.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);

	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	*c_obj = *c_template;
	c_obj->rt.dir = (t_vec3){-1.0, 0.0, 0.0};
	c_obj->rt.width = size.y;
	c_obj->rt.height = size.z;
	c_obj->rt.rel_pos = (t_vec3){size.x / -2.0, 0.0, 0.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);
	return (0);
}

#include "mrt_parse.h"
#include "print/mrt_print.h"

static int	parse_obj_cuboid_sides(t_scene *scene, t_vec3 size, t_obj *c_template);

int	parse_obj_cuboid(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_vec3	size;

	if (ft_split_count_str(split) != 10)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	if (parse_vec3(split[1], &(obj_cont(obj)->rt.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (double_from_str(split[2], 6, 3, &size.x) || size.x <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_WIDTH, NULL));
	if (double_from_str(split[3], 6, 3, &size.y) || size.y <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_HEIGHT, NULL));
	if (double_from_str(split[4], 6, 3, &size.z) || size.z <= 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DEPTH, NULL));
	if (parse_vec3(split[5], &(obj_cont(obj)->rt.rot)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_ROT, NULL));
	if (parse_material(&(obj_cont(obj)->material), &split[6], line_num))
		return (-1);
	if (parse_obj_cuboid_sides(scene, size, obj_cont(obj)))
		return (-1);
	return (0);
}

static int	parse_obj_cuboid_sides(t_scene *scene, t_vec3 size, t_obj *c_template)
{
	t_list	*obj;
	t_obj	*c_obj;

	c_template->print = &print_obj_rectangle;
	c_template->normal = &normal_rectangle;

	c_obj = c_template;
	c_obj->rt.dir = (t_vec3){0.0, 0.0, 1.0};
	c_obj->rt.width = size.x;
	c_obj->rt.height = size.y;
	c_obj->rt.rel_pos = (t_vec3){0.0, 0.0, size.z / 2.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);

	obj = obj_new(0);
	if (obj == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
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
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
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
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
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
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	*c_obj = *c_template;
	c_obj->rt.dir = (t_vec3){1.0, 0.0, 0.0};
	c_obj->rt.width = size.z;
	c_obj->rt.height = size.y;
	c_obj->rt.rel_pos = (t_vec3){size.x / 2.0, 0.0, 0.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);

	obj = obj_new(0);
	if (obj == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	*c_obj = *c_template;
	c_obj->rt.dir = (t_vec3){-1.0, 0.0, 0.0};
	c_obj->rt.width = size.z;
	c_obj->rt.height = size.y;
	c_obj->rt.rel_pos = (t_vec3){size.x / -2.0, 0.0, 0.0};
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);
	return (0);
}

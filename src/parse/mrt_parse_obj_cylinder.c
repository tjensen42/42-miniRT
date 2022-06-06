#include "mrt_parse.h"
#include "print/mrt_print.h"

static int add_caps(t_scene *scene, t_obj *c_cy);

int	parse_obj_cylinder(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (ft_split_count_str(split) != 9)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->tb.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(c_obj->tb.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	c_obj->tb.dir = vec3_normalize(c_obj->tb.dir);
	if (double_from_str(split[3], 6, 3, &(c_obj->tb.radius)) || c_obj->tb.radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_RAD, NULL));
	if (double_from_str(split[4], 6, 3, &(c_obj->tb.height)) || c_obj->tb.height <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_HEIGHT, NULL));
	if (parse_material(&(c_obj->material), &split[5], line_num))
		return (-1);
	if (add_caps(scene, c_obj))
		return (-1);
	c_obj->print = &print_obj_tube;
	c_obj->intersec = &intersec_tube;
	c_obj->normal = &normal_tube;
	return (0);
}

static int add_caps(t_scene *scene, t_obj *c_cy)
{
	t_list	*obj_top;
	t_list	*obj_bottom;

	obj_top = obj_new(0);
	if (obj_top == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj_top);
	obj_bottom = obj_new(0);
	if (obj_bottom == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj_bottom);
	obj_cont(obj_top)->material = c_cy->material;
	obj_cont(obj_top)->print = &print_obj_disc;
	obj_cont(obj_top)->intersec = &intersec_disc;
	obj_cont(obj_top)->normal = &normal_disc;
	obj_cont(obj_top)->di.radius = c_cy->tb.radius;
	*obj_cont(obj_bottom) = *obj_cont(obj_top);
	obj_cont(obj_top)->di.pos = vec3_linear_comb(1.0, c_cy->tb.pos, c_cy->tb.height / 2.0, c_cy->tb.dir);
	obj_cont(obj_top)->di.dir = c_cy->tb.dir;
	obj_cont(obj_bottom)->di.pos = vec3_linear_comb(1.0, c_cy->tb.pos, c_cy->tb.height / -2.0, c_cy->tb.dir);
	obj_cont(obj_bottom)->di.dir = vec3_scale(-1.0, c_cy->tb.dir);
	return (0);
}

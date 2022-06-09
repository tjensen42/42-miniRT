#include "mrt_parse.h"
#include "print/mrt_print.h"

static void	parse_obj_cylinder_function_ptr(t_list *obj);
static int	add_caps(t_scene *scene, t_obj *c_cy);
static int	add_cap_bottom(t_scene *scene, t_obj *c_cy, t_obj *c_obj_top);

int	parse_obj_cylinder(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;

	if (ft_split_count_str(split) != 9)
		return (print_error_scene(line_num, ERR_PARSE, ERR_NUM_PARA, NULL));
	obj = obj_new();
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	if (parse_vec3(split[1], &(obj_cont(obj)->tb.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_POS, VEC3_RANGE));
	if (parse_vec3(split[2], &(obj_cont(obj)->tb.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_DIR, VEC3_RANGE));
	obj_cont(obj)->tb.dir = vec3_norm(obj_cont(obj)->tb.dir);
	if (double_from_str(split[3], 6, 3, &(obj_cont(obj)->tb.radius))
		|| obj_cont(obj)->tb.radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_RAD, NULL));
	if (double_from_str(split[4], 6, 3, &(obj_cont(obj)->tb.height))
		|| obj_cont(obj)->tb.height <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_HEIGHT, NULL));
	if (parse_material(&(obj_cont(obj)->material), &split[5], line_num))
		return (-1);
	if (add_caps(scene, obj_cont(obj)))
		return (-1);
	parse_obj_cylinder_function_ptr(obj);
	return (0);
}

static void	parse_obj_cylinder_function_ptr(t_list *obj)
{
	obj_cont(obj)->print = &print_obj_tube;
	obj_cont(obj)->intersect = &intersect_tube;
	obj_cont(obj)->normal = &normal_tube;
}

static int	add_caps(t_scene *scene, t_obj *c_cy)
{
	t_list	*obj_top;
	t_obj	*c_obj_top;

	obj_top = obj_new();
	if (obj_top == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj_top);
	c_obj_top = obj_cont(obj_top);
	c_obj_top->material = c_cy->material;
	c_obj_top->print = &print_obj_disc;
	c_obj_top->intersect = &intersect_disc;
	c_obj_top->normal = &normal_disc;
	c_obj_top->di.radius = c_cy->tb.radius;
	c_obj_top->di.pos = vec3_lin_comb(1.0, c_cy->tb.pos,
			c_cy->tb.height / 2.0, c_cy->tb.dir);
	c_obj_top->di.dir = c_cy->tb.dir;
	if (add_cap_bottom(scene, c_cy, c_obj_top))
		return (-1);
	return (0);
}

static int	add_cap_bottom(t_scene *scene, t_obj *c_cy, t_obj *c_obj_top)
{
	t_list	*obj_bottom;
	t_obj	*c_obj_bottom;

	obj_bottom = obj_new();
	if (obj_bottom == NULL)
		return (print_error_scene(-1, ERR_PARSE, strerror(errno), NULL));
	c_obj_bottom = obj_cont(obj_bottom);
	ft_lstadd_back(&(scene->l_obj), obj_bottom);
	*c_obj_bottom = *c_obj_top;
	c_obj_bottom->di.pos = vec3_lin_comb(1.0, c_cy->tb.pos,
			c_cy->tb.height / -2.0, c_cy->tb.dir);
	c_obj_bottom->di.dir = vec3_scale(-1.0, c_cy->tb.dir);
	return (0);
}

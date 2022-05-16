#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

static int parse_is_obj(t_scene *scene, char **split, int line_num);

int	parse_is(t_scene *scene, char **split, int line_num)
{
	t_list	*is;
	t_is	*c_is;

	if (ft_split_count_str(split) != 6)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	is = is_new();
	if (is == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_is), is);
	c_is = is_cont(is);
	if (parse_vec3(split[1], &(c_is->pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (double_from_str(split[2], 6, 2, &(c_is->radius)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (parse_is_obj(scene, split, line_num))
		return (-1);
	if (double_from_str(split[5], 3, 2, &(c_is->weight)) || c_is->weight < 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid is-weight", NULL));
	c_is->linked_obj = ft_lstlast(scene->l_obj);
	c_is->print = &print_is;
	c_is->pdf_value = &pdf_sphere;
	c_is->random_dir = &random_dir_to_sphere;
	return (0);
}

static int parse_is_obj(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->pl.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (double_from_str(split[2], 6, 2, &(c_obj->sp.radius)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (parse_color(split[3], &(c_obj->material.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	c_obj->material.surface[SURF_EMISSION] = 1.0;
	if (double_from_str(split[4], 6, 2, &(c_obj->material.brightness)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid brightness", NULL));
	c_obj->print = &print_obj_sphere;
	c_obj->intersec = &intersec_sphere;
	c_obj->normal = &normal_sphere;
	return (0);
}

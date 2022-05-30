#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

static int parse_sphere_obj(t_scene *scene, char **split, int line_num);
static int parse_disc_obj(t_scene *scene, char **split, int line_num);
static int parse_rectangle_obj(t_scene *scene, char **split, int line_num);

int	parse_light_sphere(t_scene *scene, char **split, int line_num)
{
	t_list	*light;
	t_light	*c_light;

	if (ft_split_count_str(split) != 6)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	light = light_new();
	if (light == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_light), light);
	c_light = light_cont(light);
	if (parse_sphere_obj(scene, split, line_num))
		return (-1);
	if (double_from_str(split[5], 3, 2, &(c_light->weight)) || c_light->weight < 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid light-weight", NULL));
	c_light->linked_c_obj = ft_lstlast(scene->l_obj)->content;
	c_light->print = &print_light_sphere;
	c_light->pdf_value = &pdf_sphere;
	c_light->random_dir = &random_dir_to_sphere;
	return (0);
}

int	parse_light_disc(t_scene *scene, char **split, int line_num)
{
	t_list	*light;
	t_light	*c_light;

	if (ft_split_count_str(split) != 7)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	light = light_new();
	if (light == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_light), light);
	c_light = light_cont(light);
	if (parse_disc_obj(scene, split, line_num))
		return (-1);
	if (double_from_str(split[6], 3, 2, &(c_light->weight)) || c_light->weight < 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid light-weight", NULL));
	c_light->linked_c_obj = ft_lstlast(scene->l_obj)->content;
	c_light->print = &print_light_disc;
	c_light->pdf_value = &pdf_disc;
	c_light->random_dir = &random_dir_to_disc;
	return (0);
}

int	parse_light_rectangle(t_scene *scene, char **split, int line_num)
{
	t_list	*light;
	t_light	*c_light;

	if (ft_split_count_str(split) != 8)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	light = light_new();
	if (light == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_light), light);
	c_light = light_cont(light);
	if (parse_rectangle_obj(scene, split, line_num))
		return (-1);
	if (double_from_str(split[7], 3, 2, &(c_light->weight)) || c_light->weight < 0.0)
		return (print_error_scene(line_num, ERR_PARSE, "Invalid light-weight", NULL));
	c_light->linked_c_obj = ft_lstlast(scene->l_obj)->content;
	c_light->print = &print_light_rectangle;
	c_light->pdf_value = &pdf_rectangle;
	c_light->random_dir = &random_dir_to_rectangle;
	return (0);
}

static int parse_sphere_obj(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->sp.pos)))
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

static int parse_disc_obj(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	obj = obj_new(0);
	if (obj == NULL)
		return (-1);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->di.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(c_obj->di.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (double_from_str(split[3], 6, 2, &(c_obj->di.radius)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (parse_color(split[4], &(c_obj->material.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	c_obj->material.surface[SURF_EMISSION] = 1.0;
	if (double_from_str(split[5], 6, 2, &(c_obj->material.brightness)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid brightness", NULL));
	c_obj->print = &print_obj_disc;
	c_obj->intersec = &intersec_disc;
	c_obj->normal = &normal_disc;
	return (0);
}

static int parse_rectangle_obj(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

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
	if (parse_color(split[5], &(c_obj->material.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	c_obj->material.surface[SURF_EMISSION] = 1.0;
	if (double_from_str(split[6], 6, 2, &(c_obj->material.brightness)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid brightness", NULL));
	c_obj->print = &print_obj_rectangle;
	c_obj->intersec = parse_obj_rectangle_intersec(c_obj->rt.dir);
	c_obj->normal = &normal_rectangle;
	c_obj->rt.rel_pos = (t_vec3){0.0, 0.0, 0.0};
	return (0);
}

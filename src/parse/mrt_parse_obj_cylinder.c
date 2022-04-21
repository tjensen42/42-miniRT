#include "mrt_parse.h"
#include "print/mrt_print.h"

static int	parse_cylinder_caps(t_obj *c_obj, const char *caps, int line_num);

int	parse_obj_cylinder(t_scene *scene, char **split, int line_num)
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
	if (parse_vec3(split[1], &(c_obj->cy.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(c_obj->cy.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (double_from_str(split[3], 6, 2, &(c_obj->cy.radius)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (double_from_str(split[4], 6, 2, &(c_obj->cy.height)))
		return (print_error_scene(line_num, ERR_PARSE, "Invalid height", NULL));
	if (parse_cylinder_caps(c_obj, split[5], line_num))
		return (-1);
	if (parse_material(&(c_obj->material), &split[6], line_num))
		return (-1);
	c_obj->print = &print_obj_cylinder;
	c_obj->intersec = &intersec_cylinder;
	c_obj->normal = &normal_cylinder;
	return (0);
}

static int	parse_cylinder_caps(t_obj *c_obj, const char *caps, int line_num)
{
	if (ft_strcmp("none", caps) == 0)
		c_obj->cy.caps = CY_CAP_NONE;
	else if (ft_strcmp("top", caps) == 0)
		c_obj->cy.caps = CY_CAP_TOP;
	else if (ft_strcmp("bottom", caps) == 0)
		c_obj->cy.caps = CY_CAP_BOTTOM;
	else if (ft_strcmp("both", caps) == 0)
		c_obj->cy.caps = CY_CAP_BOTH;
	else
	{
		print_error_scene(line_num, ERR_PARSE, "Invalid Cap description", NULL);
		return (-1);
	}
	return (0);
}

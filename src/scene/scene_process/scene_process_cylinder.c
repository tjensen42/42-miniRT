#include "miniRT.h"
#include "../scene.h"

static int	process_cylinder_caps(t_obj *c_obj, const char *caps, int line_num);

int process_cylinder(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	if (split_count(split) != 10)
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = object_new(OBJ_CYLINDER);
	if (obj == NULL)
		return (ERROR);
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = object_cont(obj);
	if (str_to_vec3(split[1], &(c_obj->cy.pos)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (str_to_vec3(split[2], &(c_obj->cy.dir)))
		return (scene_print_error(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (str_to_double(split[3], 6, 2, &(c_obj->cy.radius)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid radius", NULL));
	if (str_to_double(split[4], 6, 2, &(c_obj->cy.height)))
		return (scene_print_error(line_num, ERR_PARSE, "Invalid height", NULL));
	if (process_cylinder_caps(c_obj, split[5], line_num))
		return (ERROR);
	if (process_material(&(c_obj->material), &split[6], line_num))
		return (ERROR);
	c_obj->print = &print_cylinder;
	return (0);
}

static int	process_cylinder_caps(t_obj *c_obj, const char *caps, int line_num)
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
		scene_print_error(line_num, ERR_PARSE, "Invalid Cap description", NULL);
		return (ERROR);
	}
	return (0);
}

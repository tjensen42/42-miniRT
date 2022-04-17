#include "miniRT.h"
#include "../scene.h"

void	print_cylinder(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = object_cont(obj);
	printf("CYLINDER: (%p)\n", obj);
	vec3_print(c_obj->cy.pos, "pos:", COLOR_BL);
	vec3_print(c_obj->cy.pos, "dir:", COLOR_CY);
	scene_print_double(c_obj->cy.radius, "radius:", COLOR_NO);
	scene_print_double(c_obj->cy.height, "height:", COLOR_NO);
	if (c_obj->cy.caps == CY_CAP_NONE)
		printf("\t%-10s %8s\n", "caps:", "none");
	else if (c_obj->cy.caps == CY_CAP_TOP)
		printf("\t%-10s %8s\n", "caps:", "top");
	else if (c_obj->cy.caps == CY_CAP_BOTTOM)
		printf("\t%-10s %8s\n", "caps:", "bottom");
	else if (c_obj->cy.caps == CY_CAP_BOTH)
		printf("\t%-10s %8s\n", "caps:", "both");
	scene_print_material(&(c_obj->material));
	printf("\n");
}

#include "mrt_print.h"

void	print_obj_disc(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = obj_cont(obj);
	printf("DISC: (%p)\n", obj);
	print_vec3(c_obj->di.pos, "pos:", COLOR_BL);
	print_vec3(c_obj->di.dir, "dir:", COLOR_CY);
	print_scene_double(c_obj->di.radius, "radius:", COLOR_NO);
	print_material(&(c_obj->material));
	printf("\n");
}

#include "mrt_print.h"

void	print_obj_sphere(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = obj_cont(obj);
	printf("SPHERE: (%p)\n", obj);
	print_vec3(c_obj->sp.pos, "pos:", COLOR_BL);
	print_scene_double(c_obj->sp.radius, "radius:", COLOR_NO);
	print_material(&(c_obj->material));
	printf("\n");
}

#include "mrt_print.h"

void	print_obj_tube(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = obj_cont(obj);
	printf("TUBE: (%p)\n", c_obj);
	print_vec3(c_obj->tb.pos, "pos:", COLOR_BL);
	print_vec3(c_obj->tb.dir, "dir:", COLOR_CY);
	print_scene_double(c_obj->tb.radius, "radius:", COLOR_NO);
	print_scene_double(c_obj->tb.height, "height:", COLOR_NO);
	print_material(&(c_obj->material));
	printf("\n");
}

#include "mrt_print.h"

void	print_obj_rectangle(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = obj_cont(obj);
	printf("RECTANGLE: (%p)\n", c_obj);
	print_vec3(c_obj->rt.pos, "pos:", COLOR_BL);
	print_vec3(c_obj->rt.dir, "dir:", COLOR_CY);
	print_scene_double(c_obj->rt.width, "width:", COLOR_NO);
	print_scene_double(c_obj->rt.height, "height:", COLOR_NO);
	print_vec3(c_obj->rt.rot, "rot:", COLOR_NO);
	print_material(&(c_obj->material));
	printf("\n");
}

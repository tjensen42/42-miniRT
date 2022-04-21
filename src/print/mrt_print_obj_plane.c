#include "mrt_print.h"

void	print_obj_plane(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = obj_cont(obj);
	printf("PLANE: (%p)\n", obj);
	print_vec3(c_obj->pl.pos, "pos:", COLOR_BL);
	print_vec3(c_obj->pl.dir, "dir:", COLOR_CY);
	print_material(&(c_obj->material));
	printf("\n");
}

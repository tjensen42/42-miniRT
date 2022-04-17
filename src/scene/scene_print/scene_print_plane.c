#include "miniRT.h"
#include "../scene.h"

void	print_plane(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = object_cont(obj);
	printf("PLANE: (%p)\n", obj);
	vec3_print(c_obj->pl.pos, "pos:", COLOR_BL);
	vec3_print(c_obj->pl.dir, "dir:", COLOR_CY);
	scene_print_material(&(c_obj->material));
	printf("\n");
}
